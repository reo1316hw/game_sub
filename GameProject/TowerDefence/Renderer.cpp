#include "pch.h"

Renderer* Renderer::mRenderer = nullptr;
static bool saveFlag = false;

/// <summary>
/// コンストラクタ
/// 隠蔽
/// </summary>
Renderer::Renderer()
	: mScreenWidth(0)
	, mScreenHeight(0)
	, mUndefineTexID(0)
	, mAmbientLight(Vector3::Zero)
	, mView(Matrix4::Identity)
	, mProjection(Matrix4::Identity)
	, mHDRRenderer(nullptr)
	, mSpriteVerts(nullptr)
	, mSpriteShader(nullptr)
	, mMeshShader(nullptr)
	, mSkinnedShader(nullptr)
	, mBasicShader(nullptr)
	, mSkyBoxShader(nullptr)
	, mParticleVertex(nullptr)
{
}

/// <summary>
/// デストラクタ
/// 隠蔽
/// </summary>
Renderer::~Renderer()
{
	delete mHDRRenderer;
}

/// <summary>
/// インスタンスを作成する
/// </summary>
void Renderer::CreateInstance()
{
	if (mRenderer == nullptr)
	{
		mRenderer = new Renderer();
	}
}

/// <summary>
/// インスタンスを削除する
/// </summary>
void Renderer::DeleteInstance()
{
	if (mRenderer != nullptr)
	{
		delete mRenderer;
		mRenderer = nullptr;
	}
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="_ScreenWidth"> スクリーンの幅 </param>
/// <param name="_ScreenHeight"> スクリーンの高さ </param>
/// <param name="_IsFullScreen"> フルスクリーンにするかのフラグ </param>
/// <returns> true : 成功 , false : 失敗 </returns>
bool Renderer::Initialize(const float& _ScreenWidth, const float& _ScreenHeight, const bool& _IsFullScreen)
{
	mScreenWidth = _ScreenWidth;
	mScreenHeight = _ScreenHeight;

	// OpenGLの各属性を設定する
	// コアOpenGLプロファイルを使う
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// OpenGLの使用バージョンを3.3に指定
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// RGBA各チャンネル8ビットのカラーバッファを使う
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// ダブルバッファを有効にする
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// ハードウェアアクセラレーションを使う
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	//ウィンドウの作成
	mWindow = SDL_CreateWindow("OpenGL Game", 1, 1,
		static_cast<int>(mScreenWidth), static_cast<int>(mScreenHeight), SDL_WINDOW_OPENGL);

	if (_IsFullScreen)
	{
		SDL_SetWindowFullscreen(mWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}

	if (!mWindow)
	{
		SDL_Log("Failed to create mWindow: %s", SDL_GetError());
		return false;
	}

	mSdlRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mSdlRenderer)
	{
		printf("SDLRendererの作成に失敗 : %s", SDL_GetError());
		return false;
	}

	// OpenGLのコンテキストを作成
	mContext = SDL_GL_CreateContext(mWindow);

	// GLEWの初期化
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}

	// 一部のプラットフォームで出る無害なエラーコードをクリアする
	glGetError();

	// シェーダーのロード
	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}
	// 未定義テクスチャ
	mUndefineTexID = GetTexture("Assets/Texture/noneTexture.png")->GetTextureID();

	// HDRレンダラー初期化
	mHDRRenderer = new HDRRenderer(mScreenWidth, mScreenHeight, 4);

	//// カリング
	glFrontFace(GL_CCW);
	glEnable(GL_FRONT_FACE);

	//スプライト用の頂点配列を作成
	CreateSpriteVerts();

	CreateParticleVerts();

	CreateCubeVerts();
	// UIの初期座標に加算される座標
	mAddPosition = Vector2::Zero;

	// Effekseer初期化
	mEffekseerRenderer = ::EffekseerRendererGL::Renderer::Create(8000, EffekseerRendererGL::OpenGLDeviceType::OpenGL3);
	mEffekseerManager = ::Effekseer::Manager::Create(8000);

	// 描画モジュール作成
	mEffekseerManager->SetSpriteRenderer(mEffekseerRenderer->CreateSpriteRenderer());
	mEffekseerManager->SetRibbonRenderer(mEffekseerRenderer->CreateRibbonRenderer());
	mEffekseerManager->SetRingRenderer(mEffekseerRenderer->CreateRingRenderer());
	mEffekseerManager->SetTrackRenderer(mEffekseerRenderer->CreateTrackRenderer());
	mEffekseerManager->SetModelRenderer(mEffekseerRenderer->CreateModelRenderer());

	// Effekseer用のテクスチャ・モデル・マテリアルローダー
	mEffekseerManager->SetTextureLoader(mEffekseerRenderer->CreateTextureLoader());
	mEffekseerManager->SetModelLoader(mEffekseerRenderer->CreateModelLoader());
	mEffekseerManager->SetMaterialLoader(mEffekseerRenderer->CreateMaterialLoader());

	return true;
}

/// <summary>
/// 終了処理
/// </summary>
void Renderer::Shutdown()
{
	delete mSpriteVerts;
	mSpriteShader->Unload();
	delete mSpriteShader;
	mMeshShader->Unload();
	delete mMeshShader;
	mBasicShader->Unload();
	delete mBasicShader;

	// Effekseer関連の破棄
	mEffekseerManager.Reset();
	mEffekseerRenderer.Reset();

	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
}

/// <summary>
/// ロードしたデータの解放
/// </summary>
void Renderer::UnloadData()
{
	// すべてのテクスチャのデータを解放
	for (auto i : mTextures)
	{
		i.second->Unload();
		delete i.second;
	}
	mTextures.clear();

	// すべてのメッシュのデータを解放
	for (auto i : mMeshes)
	{
		i.second->Unload();
		delete i.second;
	}
	// Unload skeletons
	for (auto s : mSkeletons)
	{
		delete s.second;
	}
	// Unload animations
	for (auto a : mAnims)
	{
		delete a.second;
	}

	mMeshes.clear();
}

/// <summary>
/// 描画処理
/// </summary>
void Renderer::Draw()
{
	mHDRRenderer->HdrRecordBegin();
	{
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);

		// スカイボックス描画
		if (mActiveSkyBox != nullptr)
		{
			mSkyBoxShader->SetActive();
			// ゲームの空間に合わせるためのオフセット行列をセット
			Matrix4 offset = Matrix4::CreateRotationX(Math::ToRadians(90.0f));
			mSkyBoxShader->SetMatrixUniform("u_offset", offset);

			// Uniformに逆行列をセット
			Matrix4 InvView = mView;
			InvView.Invert();
			InvView.Transpose();
			mSkyBoxShader->SetMatrixUniform("u_invView", InvView);
			mSkyBoxShader->SetMatrixUniform("u_projection", mProjection);
			mSkyBoxShader->SetIntUniform("u_skybox", 0);

			mActiveSkyBox->Draw(mSkyBoxShader);
		}

		// メッシュコンポーネントの描画
		// 基本的なメッシュシェーダーをアクティブにする
		mMeshShader->SetActive();
		// ビュー射影行列を更新する
		mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);
		// シェーダーに渡すライティング情報を更新する
		SetLightUniforms(mMeshShader, mView);
		// すべてのメッシュの描画
		for (auto mc : mMeshComponents)
		{
			if (mc->GetVisible())
			{
				mc->Draw(mMeshShader);
			}
		}
	}
	mHDRRenderer->HdrRecordEnd();

	//////////////////////////////////////////////////////////////////
	// HDR Bloom の作成＆合成
	/////////////////////////////////////////////////////////////////
	mHDRRenderer->HiBrightBlurCreate();
	mHDRRenderer->HdrTonemapAndBrightBlurCombine();

	// HDRBufferにレンダリングしたときのDepth情報をスクリーンにコピー
	mHDRRenderer->CopyDepthToScreen();

	// 当たり判定デバッグBoxの表示
	PHYSICS->DebugShowBox();
	
	mBasicShader->SetActive();
	mBasicShader->SetMatrixUniform("uViewProj", mView * mProjection);

	// Draw any skinned mMeshes now
	// Draw any skinned mMeshes now
	mSkinnedShader->SetActive();
	// Update mView-mProjection matrix
	mSkinnedShader->SetMatrixUniform("uViewProj", mView * mProjection);
	// Update lighting uniforms
	SetLightUniforms(mSkinnedShader, mView);
	for (auto sk : mSkeletalMeshes)
	{
		if (sk->GetVisible())
		{
			sk->Draw(mSkinnedShader);
		}
	}

	DrawParticle();

	// UIの描画
	//アルファブレンディングを有効にする
	glEnable(GL_BLEND);
	//デプスバッファ法を無効にする
	glDisable(GL_DEPTH_TEST);

	// RGB成分とα成分のブレンディング方法を別々に設定
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	// RGB成分とアルファ成分に別々の混合係数を設定
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	// スプライトシェーダーをアクティブにする/スプライト頂点配列を有効にする
	mSpriteShader->SetActive();
	mSpriteVerts->SetActive();
	// すべてのスプライトの描画
	for (auto sprite : mSprites)
	{
		if (sprite->GetVisible())
		{
			sprite->Draw(mSpriteShader);
		}
	}

		// バッファを交換
	SDL_GL_SwapWindow(mWindow);
}

/// <summary>
/// 全てのパーティクルを描画準備
/// </summary>
void Renderer::DrawParticle()
{

	std::sort(mParticles.begin(), mParticles.end(), std::greater<ParticleComponent*>());

	if (mParticles.size() == 0)
	{
		return;
	}
	// ブレンドモード初期状態取得
	ParticleComponent::ParticleBlendType blendType, prevType;
	auto itr = mParticles.begin();
	blendType = prevType = (*itr)->GetBlendType();

	// テクスチャID初期状態取得
	int nowTexture, prevTexture;
	nowTexture = prevTexture = (*itr)->GetTexture()->GetTextureID();

	// ビュープロジェクション行列
	Matrix4 viewProjectionMat;
	viewProjectionMat = mView * mProjection;

	// シェーダーON
	mParticleShader->SetActive();
	mParticleShader->SetMatrixUniform("uViewProj", viewProjectionMat);

	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);

	// すべてのパーティクルを描画
	ChangeBlendMode(blendType);
	ChangeTexture(nowTexture);

	for (auto particle : mParticles)
	{
		if (particle->GetVisible())
		{
			//ブレンドモード変更が必要なら変更する
			blendType = particle->GetBlendType();
			blendType = particle->GetBlendType();
			if (blendType != prevType)
			{
				ChangeBlendMode(blendType);
			}
			// テクスチャ変更が必要なら変更する
			nowTexture = particle->GetTexture()->GetTextureID();
			if (nowTexture != prevTexture)
			{
				ChangeTexture(nowTexture);
			}

			// パーティクル描画
			particle->Draw(mParticleShader);

			// 前回描画状態として保存
			prevType = blendType;
			prevTexture = nowTexture;
		}
	}
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
}

void Renderer::SetViewMatrix(const Matrix4& view)
{
	Matrix4 tmp = view;
	mView = view;

	// Effekseer に座標系を合わせて行列をセットする
	Effekseer::Matrix44 efCam;
	tmp.mat[0][0] *= -1;
	tmp.mat[0][1] *= -1;
	tmp.mat[1][2] *= -1;
	tmp.mat[2][2] *= -1;
	tmp.mat[3][2] *= -1;

	efCam = tmp;
	RENDERER->GetEffekseerRenderer()->SetCameraMatrix(efCam);
}

void Renderer::SetProjMatrix(const Matrix4& proj)
{
	mProjection = proj;

	// Effekseer に座標系を合わせて行列をセットする
	Matrix4 tmp = proj;
	tmp.mat[2][2] *= -1;
	tmp.mat[2][3] *= -1;

	Effekseer::Matrix44 eProj;
	eProj = tmp;
	RENDERER->GetEffekseerRenderer()->SetProjectionMatrix(eProj);
}

/// <summary>
/// スプライトの追加
/// </summary>
/// <param name="_spriteComponent"> 追加するSpriteComponentクラスのポインタ </param>
void Renderer::AddSprite(SpriteComponent* _spriteComponent)
{
	// 今あるスプライトから挿入する場所の検索
	// (DrawOrderが小さい順番に描画するため)
	int myDrawOrder = _spriteComponent->GetDrawOrder();
	auto iter = mSprites.begin();
	for (;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// 検索した場所のiterの場所に挿入
	mSprites.insert(iter, _spriteComponent);
}

/// <summary>
/// スプライトの削除
/// </summary>
/// <param name="_spriteComponent"> 削除するSpriteComponentクラスのポインタ </param>
void Renderer::RemoveSprite(SpriteComponent* _spriteComponent)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), _spriteComponent);
	mSprites.erase(iter);
}

/// <summary>
/// パーティクルの追加
/// </summary>
/// <param name="_particleComponent"> 追加するParticleObjectクラスのポインタ </param>
void Renderer::AddParticle(ParticleComponent * _particleComponent)
{
	int myDrawOrder = _particleComponent->GetDrawOrder();
	auto iter = mParticles.begin();
	for (;
		iter != mParticles.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}
	mParticles.insert(iter, _particleComponent);
}

/// <summary>
/// パーティクルの削除
/// </summary>
/// <param name="_particleComponent"> 削除するParticleObjectクラスのポインタ </param>
void Renderer::RemoveParticle(ParticleComponent * _particleComponent)
{
	auto iter = std::find(mParticles.begin(), mParticles.end(), _particleComponent);
	mParticles.erase(iter);
}

/// <summary>
/// メッシュコンポーネントの追加
/// </summary>
/// <param name="_meshComponent"> 追加するMeshComponentクラスのポインタ </param>
void Renderer::AddMeshComponent(MeshComponent* _meshComponent)
{
	if (_meshComponent->GetIsSkeltal())
	{
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(_meshComponent);
		mSkeletalMeshes.emplace_back(sk);
	}
	else
	{
		mMeshComponents.emplace_back(_meshComponent);
	}
}

/// <summary>
/// メッシュコンポーネントの削除
/// </summary>
/// <param name="_meshComponent"> 削除するMeshComponentクラスのポインタ </param>
void Renderer::RemoveMeshComponent(MeshComponent* _meshComponent)
{
	if (_meshComponent->GetIsSkeltal())
	{
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(_meshComponent);
		auto iter = std::find(mSkeletalMeshes.begin(), mSkeletalMeshes.end(), sk);
		mSkeletalMeshes.erase(iter);
	}
	else
	{
		auto iter = std::find(mMeshComponents.begin(), mMeshComponents.end(), _meshComponent);
		mMeshComponents.erase(iter);
	}
}

/// <summary>
/// スケルトンモデルを取得
/// </summary>
/// <param name="_FileName"> 取得したいスケルトンモデルのファイル名 </param>
/// <returns> スケルトンクラスのポインタ </returns>
const Skeleton * Renderer::GetSkeleton(const char* _FileName)
{
	std::string file(_FileName);
	auto iter = mSkeletons.find(file);
	if (iter != mSkeletons.end())
	{
		return iter->second;
	}
	else
	{
		Skeleton* sk = new Skeleton();
		if (sk->Load(file))
		{
			mSkeletons.emplace(file, sk);
		}
		else
		{
			delete sk;
			sk = nullptr;
		}
		return sk;
	}
}

/// <summary>
/// スケルトンアニメーションを取得
/// </summary>
/// <param name="_FileName"> 取得したいスケルトンアニメーションのファイル名 </param>
/// <param name="_Loop"> アニメーションをループさせるか </param>
/// <returns> アニメーションクラスのポインタ </returns>
const Animation * Renderer::GetAnimation(const char* _FileName, const bool& _Loop)
{
	auto iter = mAnims.find(_FileName);
	if (iter != mAnims.end())
	{
		return iter->second;
	}
	else
	{
		Animation* anim = new Animation();
		if (anim->Load(_FileName, _Loop))
		{
			mAnims.emplace(_FileName, anim);
		}
		else
		{
			delete anim;
			anim = nullptr;
		}
		return anim;
	}
}

/// <summary>
/// テクスチャを取得
/// </summary>
/// <param name="_FileName"> 取得したいテクスチャのファイル名 </param>
/// <returns> テクスチャクラスのポインタ </returns>
Texture* Renderer::GetTexture(const std::string& _FileName)
{
	Texture* texture = nullptr;
	//すでに作成されてないか調べる
	auto itr = mTextures.find(_FileName);
	if (itr != mTextures.end())
	{
		texture = itr->second;
	}
	//作成済みでない場合、新しくテクスチャを作成
	else
	{
		texture = new Texture();
		if (texture->Load(_FileName))
		{
			mTextures.emplace(_FileName, texture);
		}
		else
		{
			delete texture;
			texture = nullptr;
		}
	}

	return texture;
}

/// <summary>
/// メッシュを取得
/// </summary>
/// <param name="_FileName"> 取得したいメッシュのファイル名 </param>
/// <returns> メッシュクラスのポインタ </returns>
Mesh* Renderer::GetMesh(const std::string& _FileName)
{
	Mesh* m = nullptr;
	//すでに作成されてないか調べる
	auto iter = mMeshes.find(_FileName);
	if (iter != mMeshes.end())
	{
		m = iter->second;
	}
	//作成済みでない場合、新しくメッシュを作成
	else
	{
		m = new Mesh();
		if (m->Load(_FileName, this))
		{
			mMeshes.emplace(_FileName, m);
		}
		else
		{
			delete m;
			m = nullptr;
		}
	}
	return m;
}

/// <summary>
/// シェーダーの読み込み
/// </summary>
/// <returns> true : 成功 , false : 失敗 </returns>
bool Renderer::LoadShaders()
{
	// スプライトシェーダーの作成
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}

	mSpriteShader->SetActive();
	// ビュー行列の設定
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(mScreenWidth, mScreenHeight);
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);

	// 標準のメッシュシェーダーの作成
	mMeshShader = new Shader();
	if (!mMeshShader->Load("Shaders/Phong.vert", "Shaders/HDRMesh.frag"))
	{
		return false;
	}

	mBasicShader = new Shader();
	if (!mBasicShader->Load("Shaders/BasicMesh.vert", "Shaders/BasicMesh.frag"))
	{
		return false;
	}

	mParticleShader = new Shader();
	if (!mParticleShader->Load("Shaders/Phong.vert", "Shaders/Particle.frag"))
	{
		printf("シェーダー読み込み失敗\n");
	}

	mSkinnedShader = new Shader();
	if (!mSkinnedShader->Load("Shaders/Skinned.vert", "Shaders/Phong.frag"))
	{
		return false;
	}
	mSkinnedShader->SetActive();
	mSkinnedShader->SetMatrixUniform("uViewProj", mView * mProjection);

	// 標準のメッシュシェーダーの作成
	mSkyBoxShader = new Shader();
	if (!mSkyBoxShader->Load("Shaders/gBuffer_SkyBox.vert", "Shaders/gBuffer_SkyBox.frag"))
	{
		return false;
	}

	// メッシュ
	mMeshShader->SetActive();

	// ビュー行列の設定
	mView = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
	mProjection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(90.0f),
		mScreenWidth, mScreenHeight, 10.0f, 10000.0f);

	mBasicShader->SetActive();
	mBasicShader->SetMatrixUniform("uViewProj", mView * mProjection);
	return true;
}

/// <summary>
/// スプライト用の頂点バッファとインデックスバッファの作成
/// </summary>
void Renderer::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // 左上
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // 右上
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // 右下
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // 左下
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}

/// <summary>
/// パーティクル用の頂点バッファとインデックスバッファの作成
/// </summary>
void Renderer::CreateParticleVerts()
{
	float vertices[] = {
		-0.5f, 0.f, 0.5f, 0.f, 0.f, 0.0f, 0.f, 0.f, // top left
		 0.5f, 0.f, 0.5f, 0.f, 0.f, 0.0f, 1.f, 0.f, // top right
		 0.5f, 0.f,-0.5f, 0.f, 0.f, 0.0f, 1.f, 1.f, // bottom right
		-0.5f, 0.f,-0.5f, 0.f, 0.f, 0.0f, 0.f, 1.f  // bottom left
	};

	unsigned int indices[] = {
		0, 2, 1,
		2, 0, 3
	};
	mParticleVertex = new VertexArray(vertices, 4, VertexArray::PosNormTex, indices, 6);
}

/// <summary>
/// キューブマップ(スカイボックス用)頂点配列定義
/// </summary>
void Renderer::CreateCubeVerts()
{
	mCubeVerts = new VertexArray();
	mCubeVerts->CreateCubeVerts();
}

/// <summary>
/// パーティクルの頂点配列を設定
/// </summary>
void Renderer::SetParticleVertex()
{
	mParticleVertex->SetActive();
}

/// <summary>
/// 光源情報をシェーダーの変数にセットする
/// </summary>
/// <param name="_shader"> セットするShaderクラスのポインタ </param>
/// <param name="_View"> ビュー行列 </param>
void Renderer::SetLightUniforms(Shader* _shader, const Matrix4& _View)
{
	// ビュー行列を逆行列にする
	Matrix4 invView = _View;
	invView.Invert();
	_shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
	// 環境光の設定
	_shader->SetVectorUniform("uAmbientLight", mAmbientLight);
	// 平行光源の設定
	_shader->SetVectorUniform("uDirLight.mDirection",
		mDirLight.m_direction);
	_shader->SetVectorUniform("uDirLight.mDiffuseColor",
		mDirLight.m_diffuseColor);
	_shader->SetVectorUniform("uDirLight.mSpecColor",
		mDirLight.m_specColor);
}

EffekseerEffect* Renderer::GetEffect(const char16_t* fileName)
{
	// エフェクトファイルを一度読み込んだかを確認
	EffekseerEffect* effect = nullptr;
	auto iter = mEffects.find(fileName);

	// 一度読んでいるなら返す
	if (iter != mEffects.end())
	{
		return iter->second;
	}
	//読んでいなければ新規追加
	effect = new EffekseerEffect;
	if (effect->LoadEffect(fileName))
	{
		mEffects.emplace(fileName, effect);
	}
	else
	{
		delete effect;
		effect = nullptr;
	}
	return effect;
}


/// <summary>
/// ブレンドモードを変更する
/// </summary>
/// <param name="_blendType"> ブレンドモード </param>
void Renderer::ChangeBlendMode(ParticleComponent::ParticleBlendType blendType)
{
	switch (blendType)
	{
	case ParticleComponent::eParticleBlendAdd:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);  //加算合成
		break;
	case ParticleComponent::eParticleBlendAlpha:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // アルファブレンド
		break;
	case ParticleComponent::eParticleBlendMult:
		glBlendFunc(GL_ZERO, GL_SRC_COLOR); //乗算合成
		break;
	default:
		break;
	}
}

/// <summary>
/// テクスチャを変更
/// </summary>
/// <param name="_ChangeTextureID"> テクスチャID </param>
void Renderer::ChangeTexture(const int& _ChangeTextureID)
{
	glBindTexture(GL_TEXTURE_2D, _ChangeTextureID);
}

/// <summary>
/// ワールド座標でのカメラ位置算出
/// </summary>
/// <returns> カメラ位置(ワールド座標) </returns>
Vector3 Renderer::CalcCameraPos()
{
	// ビュー行列よりワールドでのカメラ位置算出
	Matrix4 transMat = mView;

	// ビュー行列の移動成分抜き取る
	Vector3 v;
	v.x = -1.0f * mView.mat[3][0];
	v.y = -1.0f * mView.mat[3][1];
	v.z = -1.0f * mView.mat[3][2];

	//移動成分を取り除いたあと転置して、回転部分の逆変換を作る
	transMat.mat[3][0] = transMat.mat[3][1] = transMat.mat[3][2] = 0.0f;
	transMat.Transpose();

	return Vector3(Vector3::Transform(v, transMat));
}
