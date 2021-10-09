#include "pch.h"

Renderer* Renderer::mRenderer = nullptr;
static bool saveFlag = false;

void Renderer::SetParticleVertex()
{
	mParticleVertex->SetActive();
}

Renderer::Renderer()
	: mSpriteShader(nullptr)
	, mSpriteVerts(nullptr)
	, mUiShader(nullptr)
	, mUiVerts(nullptr)
	, mMeshShader(nullptr)
	, mInvisibleMeshShader(nullptr)
	, mBasicShader(nullptr)
	, mParticleVertex(nullptr)
	, mView(Matrix4::Identity)
	, mProjection(Matrix4::Identity)
	, mScreenWidth(0)
	, mScreenHeight(0)
	, mAmbientLight(Vector3::Zero)
	, mSkinnedShader(nullptr)
	, mUndefineTexID(0)
	, mHDRRenderer(nullptr)
{
}

Renderer::~Renderer()
{
	delete mHDRRenderer;
}

/*
@brief  インスタンスを作成する
*/
void Renderer::CreateInstance()
{
	if (mRenderer == nullptr)
	{
		mRenderer = new Renderer();
	}
}

/*
@brief  インスタンスを削除する
*/
void Renderer::DeleteInstance()
{
	if (mRenderer != nullptr)
	{
		delete mRenderer;
		mRenderer = nullptr;
	}
}

/*
@brief  初期化処理
@return true : 成功 , false : 失敗
*/
bool Renderer::Initialize(float _ScreenWidth, float _screenHeight, bool _fullScreen)
{
	mScreenWidth = _ScreenWidth;
	mScreenHeight = _screenHeight;

	// OpenGLの各属性を設定する
	// コアOpenGLプロファイルを使う
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// OpenGLの使用バージョンを3.3に指定
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
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

	if (_fullScreen)
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

	////// カリング
	//glFrontFace(GL_CCW);
	//glEnable(GL_FRONT_FACE);

	//スプライト用の頂点配列を作成
	CreateSpriteVerts();

	CreateParticleVerts();

	// UIの初期座標に加算される座標
	mAddPosition = Vector2::Zero;

	return true;
}

/*
@brief  終了処理
*/
void Renderer::Shutdown()
{
	delete mSpriteVerts;
	mSpriteShader->Unload();
	delete mSpriteShader;
	delete mUiVerts;
	mUiShader->Unload();
	delete mUiShader;
	mMeshShader->Unload();
	delete mMeshShader;
	mInvisibleMeshShader->Unload();
	delete mInvisibleMeshShader;
	mBasicShader->Unload();
	delete mBasicShader;
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
}

/*
@brief  ロードしたデータの解放
*/
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

/*
@brief  描画処理
*/
void Renderer::Draw()
{

	mHDRRenderer->HdrRecordBegin();
	{
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

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);

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


	//// UIの描画
	//// アルファブレンディングを有効にする
	//glEnable(GL_BLEND);
	//// デプスバッファ法を無効にする
	//glDisable(GL_DEPTH_TEST);
	//// RGB成分とα成分のブレンディング方法を別々に設定
	//glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	//// RGB成分とアルファ成分に別々の混合係数を設定
	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	//// UIシェーダーをアクティブにする/スプライト頂点配列を有効にする
	//mUiShader->SetActive();
	//mUiVerts->SetActive();
	//// すべてのUIの描画
	//for (auto ui : mUis)
	//{
	//	if (ui->GetVisible())
	//	{
	//		ui->Draw(mUiShader, ui->GetOwner()->GetPosition());
	//	}
	//}

		// バッファを交換
	SDL_GL_SwapWindow(mWindow);
}

/*
@brief  スプライトの追加
@param	_spriteComponent　追加するSpriteComponentクラスのポインタ
*/
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

/*
@brief スプライトの削除
@param	_spriteComponent　削除するSpriteComponentクラスのポインタ
*/
void Renderer::RemoveSprite(SpriteComponent* _spriteComponent)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), _spriteComponent);
	mSprites.erase(iter);
}

void Renderer::AddUI(UIComponent* _ui)
{
	// 今あるスプライトから挿入する場所の検索
	// (DrawOrderが小さい順番に描画するため)
	int myUiDrawOrder = _ui->GetDrawOrder();
	auto iterUi = mUis.begin();
	for (;
		iterUi != mUis.end();
		++iterUi)
	{
		if (myUiDrawOrder < (*iterUi)->GetDrawOrder())
		{
			break;
		}
	}

	// 検索した場所のiterの場所に挿入
	mUis.insert(iterUi, _ui);
}

void Renderer::RemoveUI(UIComponent* _ui)
{
	auto iterUi = std::find(mUis.begin(), mUis.end(), _ui);
	mUis.erase(iterUi);
}

/*
@brief  パーティクルの追加
@param	_particleComponent　追加するParticleObjectクラスのポインタ
*/
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

/*
@brief  スプライトの削除
@param	削除するParticleObjectクラスのポインタ
*/
void Renderer::RemoveParticle(ParticleComponent * _particleComponent)
{
	auto iter = std::find(mParticles.begin(), mParticles.end(), _particleComponent);
	mParticles.erase(iter);
}

/*
@brief  メッシュコンポーネントの追加
@param	_meshComponent　追加するMeshComponentクラスのポインタ
*/
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

/*
@brief  メッシュコンポーネントの削除
@param	_meshComponent　削除するMeshComponentクラスのポインタ
*/
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

/*
@brief  インビジブルメッシュコンポーネントの追加
@param	_invisibleMeshComponent　追加するInvisibleMeshComponentクラスのポインタ
*/
void Renderer::AddInvisibleMeshComponent(InvisibleMeshComponent* _invisibleMeshComponent)
{
	/*if (_invisibleMeshComponent->GetIsSkeltal())
	{
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(_invisibleMeshComponent);
		mSkeletalMeshes.emplace_back(sk);
	}
	else
	{
		invisibleMeshComponent.emplace_back(_meshComponent);
	}*/

	mInvisibleMeshComponents.emplace_back(_invisibleMeshComponent);
}

/*
@brief  インビジブルメッシュコンポーネントの削除
@param	_invisibleMeshComponent　削除するInvisibleMeshComponentクラスのポインタ
*/
void Renderer::RemoveInvisibleMeshComponent(InvisibleMeshComponent* _invisibleMeshComponent)
{
	/*if (_meshComponent->GetIsSkeltal())
	{
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(_meshComponent);
		auto iter = std::find(mSkeletalMeshes.begin(), mSkeletalMeshes.end(), sk);
		mSkeletalMeshes.erase(iter);
	}
	else
	{
		auto iter = std::find(mMeshComponents.begin(), mMeshComponents.end(), _meshComponent);
		mMeshComponents.erase(iter);
	}*/
	
	auto iter = std::find(mInvisibleMeshComponents.begin(), mInvisibleMeshComponents.end(), _invisibleMeshComponent);
	mInvisibleMeshComponents.erase(iter);
}

/*
@param _fileName モデルへのアドレス
@return スケルトンモデルの取得
*/
const Skeleton * Renderer::GetSkeleton(const char * _fileName)
{
	std::string file(_fileName);
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

/*
@param _fileName アニメーションへのアドレス
@return スケルトンアニメーションの取得
*/
const Animation * Renderer::GetAnimation(const char * _fileName, bool _loop)
{
	auto iter = mAnims.find(_fileName);
	if (iter != mAnims.end())
	{
		return iter->second;
	}
	else
	{
		Animation* anim = new Animation();
		if (anim->Load(_fileName, _loop))
		{
			mAnims.emplace(_fileName, anim);
		}
		else
		{
			delete anim;
			anim = nullptr;
		}
		return anim;
	}
}

/*
@brief  テクスチャの取得
@param	_fileName　取得したいテクスチャのファイル名
@return Textureクラスのポインタ
*/
Texture* Renderer::GetTexture(const std::string& _fileName)
{
	Texture* texture = nullptr;
	//すでに作成されてないか調べる
	auto itr = mTextures.find(_fileName);
	if (itr != mTextures.end())
	{
		texture = itr->second;
	}
	//作成済みでない場合、新しくテクスチャを作成
	else
	{
		texture = new Texture();
		if (texture->Load(_fileName))
		{
			mTextures.emplace(_fileName, texture);
		}
		else
		{
			delete texture;
			texture = nullptr;
		}
	}

	return texture;
}

/*
@brief  メッシュの取得
@param	_fileName 取得したいメッシュのファイル名
@return Meshクラスのポインタ
*/
Mesh* Renderer::GetMesh(const std::string& _fileName)
{
	Mesh* m = nullptr;
	//すでに作成されてないか調べる
	auto iter = mMeshes.find(_fileName);
	if (iter != mMeshes.end())
	{
		m = iter->second;
	}
	//作成済みでない場合、新しくメッシュを作成
	else
	{
		m = new Mesh();
		if (m->Load(_fileName, this))
		{
			mMeshes.emplace(_fileName, m);
		}
		else
		{
			delete m;
			m = nullptr;
		}
	}
	return m;
}

/*
@brief  シェーダーの読み込み
@return true : 成功 , false : 失敗
*/
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

	// UIシェーダーの作成
	mUiShader = new Shader();
	if (!mUiShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}

	mUiShader->SetActive();
	// ビュー行列の設定
	Matrix4 viewUiProj = Matrix4::CreateSimpleViewProj(mScreenWidth, mScreenHeight);
	mUiShader->SetMatrixUniform("uViewProj", viewUiProj);

	// 標準のメッシュシェーダーの作成
	mMeshShader = new Shader();
	if (!mMeshShader->Load("Shaders/Phong.vert", "Shaders/HDRMesh.frag"))
	{
		return false;
	}

	// インビジブルメッシュシェーダーの作成
	mInvisibleMeshShader = new Shader();
	if (!mInvisibleMeshShader->Load("Shaders/Phong.vert", "Shaders/HDRMesh.frag"))
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

	// メッシュ
	mMeshShader->SetActive();

	// インビジブルメッシュ
	mInvisibleMeshShader->SetActive();

	// ビュー行列の設定
	mView = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
	mProjection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(90.0f),
		mScreenWidth, mScreenHeight, 10.0f, 10000.0f);

	mInvisibleMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);

	mBasicShader->SetActive();
	mBasicShader->SetMatrixUniform("uViewProj", mView * mProjection);
	return true;
}

/*
@brief  Sprite用の頂点バッファとインデックスバッファの作成
*/
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
	mUiVerts = new VertexArray(vertices, 4, indices, 6);
}

// パーティクル頂点作成
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

void Renderer::DrawParticle()
{

	std::sort(mParticles.begin(), mParticles.end(), std::greater<ParticleComponent*>());

	if (mParticles.size() == 0)
	{
		return;
	}
	// ブレンドモード初期状態取得
	ParticleComponent::PARTICLE_BLEND_ENUM blendType, prevType;
	auto itr = mParticles.begin();
	blendType = prevType = (*itr)->GetBlendType();

	// テクスチャID初期状態取得
	int nowTexture, prevTexture;
	nowTexture = prevTexture = (*itr)->GetTextureID();

	// ビュープロジェクション行列
	Matrix4 viewProjectionMat;
	viewProjectionMat = mView * mProjection;

	// シェーダーON
	mParticleShader->SetActive();
	mParticleShader->SetMatrixUniform("uViewProj", viewProjectionMat);

	// 全てのパーティクルのビルボード行列をセット
	Matrix4 tmp;
	tmp = Matrix4::CreateRotationX(-0.5f * 3.14159f);
	(*itr)->SetBillboardMat(tmp);

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
			nowTexture = particle->GetTextureID();
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

void Renderer::Draw3DScene(unsigned int _framebuffer, const Matrix4 & _view, const Matrix4 & _proj, float _viewPortScale, bool _lit)
{
	// Set the current frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

	// Set viewport size based on scale
	glViewport(0, 0,
		static_cast<int>(mScreenWidth * _viewPortScale),
		static_cast<int>(mScreenHeight * _viewPortScale)
	);

	// Clear color buffer/depth buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw mesh components
	// Enable depth buffering/disable alpha blend
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	// Set the mesh shader active
	mMeshShader->SetActive();
	// Update mView-mProjection matrix
	mMeshShader->SetMatrixUniform("uViewProj", _view * _proj);
	// Update lighting uniforms
	if (_lit)
	{
		SetLightUniforms(mMeshShader, _view);
	}
	for (auto mc : mMeshComponents)
	{
		if (mc->GetVisible())
		{
			mc->Draw(mMeshShader);
		}
	}

}

//void Renderer::DrawTexture(class Texture* texture,int index, int xDyvNum , int yDivNum, const Vector2& offset, float scale, float alpha)
//{
//	// テクスチャの幅・高さでスケーリング
//	Matrix4 scaleMat = Matrix4::CreateScale(
//		static_cast<float>(texture->GetWidth()) * scale,
//		static_cast<float>(texture->GetHeight()) * scale,
//		1.0f);
//	// スクリーン位置の平行移動
//	Matrix4 transMat = Matrix4::CreateTranslation(
//		Vector3(offset.x - (mScreenWidth * 0.5f),
//			(mScreenHeight * 0.5f) - offset.y, 0.0f));
//	// ワールド変換
//	Matrix4 world = scaleMat * transMat;
//	mSpriteShader->SetMatrixUniform("uWorldTransform", world);
//	mSpriteShader->SetFloatUniform("alpha", alpha);
//	// テクスチャセット
//	texture->SetActive();
//	// 四角形描画
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
//
//}

//void Renderer::DrawTexture(Texture* texture, const Vector2& offset, float scale, float alpha)
//{
//	DrawTexture(texture, 0, 1, 1, offset, scale, alpha);
//}

/*
@brief  光源情報をシェーダーの変数にセットする
@param _shader セットするShaderクラスのポインタ
*/
void Renderer::SetLightUniforms(Shader* _shader, const Matrix4& _view)
{
	// ビュー行列を逆行列にする
	Matrix4 invView = _view;
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

void Renderer::ChangeBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM blendType)
{
	switch (blendType)
	{
	case ParticleComponent::PARTICLE_BLEND_ENUM_ADD:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);  //加算合成
		break;
	case ParticleComponent::PARTICLE_BLEND_ENUM_ALPHA:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // アルファブレンド
		break;
	case ParticleComponent::PARTICLE_BLEND_ENUM_MULT:
		glBlendFunc(GL_ZERO, GL_SRC_COLOR); //乗算合成
		break;
	default:
		break;
	}
}

void Renderer::ChangeTexture(int _changeTextureID)
{
	glBindTexture(GL_TEXTURE_2D, _changeTextureID);
}

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
