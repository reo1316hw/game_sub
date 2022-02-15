#include "pch.h"

Renderer* Renderer::mRenderer = nullptr;
static bool saveFlag = false;

/// <summary>
/// �R���X�g���N�^
/// �B��
/// </summary>
Renderer::Renderer()
	: MFontTextureNum(100)
	, MFontSize(72)
	, mScreenWidth(0)
	, mScreenHeight(0)
	, mUndefineTexID(0)
	, mAmbientLight(Vector3::Zero)
	, mView(Matrix4::Identity)
	, mProjection(Matrix4::Identity)
	, mHDRRenderer(nullptr)
	, mMeshShadowHDRShader(nullptr)
	, mSkinnedShadowHDRShader(nullptr)
	, mSpriteVerts(nullptr)
	, mSpriteShader(nullptr)
	/*, mMeshShader(nullptr)
	, mSkinnedShader(nullptr)*/
	, mSkyBoxShader(nullptr)
	, mParticleVertex(nullptr)
	, mDepthMapRender(nullptr)
	, mSkinnedDepthShader(nullptr)
{
}

/// <summary>
/// �f�X�g���N�^
/// �B��
/// </summary>
Renderer::~Renderer()
{
	delete mDepthMapRender;
	delete mHDRRenderer;
}

/// <summary>
/// �C���X�^���X���쐬����
/// </summary>
void Renderer::CreateInstance()
{
	if (mRenderer == nullptr)
	{
		mRenderer = new Renderer();
	}
}

/// <summary>
/// �C���X�^���X���폜����
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
/// ����������
/// </summary>
/// <param name="_ScreenWidth"> �X�N���[���̕� </param>
/// <param name="_ScreenHeight"> �X�N���[���̍��� </param>
/// <param name="_IsFullScreen"> �t���X�N���[���ɂ��邩�̃t���O </param>
/// <returns> true : ���� , false : ���s </returns>
bool Renderer::Initialize(const float& _ScreenWidth, const float& _ScreenHeight, const bool& _IsFullScreen)
{
	mScreenWidth = _ScreenWidth;
	mScreenHeight = _ScreenHeight;

	// OpenGL�̊e������ݒ肷��
	// �R�AOpenGL�v���t�@�C�����g��
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// OpenGL�̎g�p�o�[�W������3.3�Ɏw��
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// RGBA�e�`�����l��8�r�b�g�̃J���[�o�b�t�@���g��
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// �_�u���o�b�t�@��L���ɂ���
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// �n�[�h�E�F�A�A�N�Z�����[�V�������g��
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	//�E�B���h�E�̍쐬
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
		printf("SDLRenderer�̍쐬�Ɏ��s : %s", SDL_GetError());
		return false;
	}

	// OpenGL�̃R���e�L�X�g���쐬
	mContext = SDL_GL_CreateContext(mWindow);

	// GLEW�̏�����
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}

	// �ꕔ�̃v���b�g�t�H�[���ŏo�閳�Q�ȃG���[�R�[�h���N���A����
	glGetError();

	// �V�F�[�_�[�̃��[�h
	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}
	// ����`�e�N�X�`��
	mUndefineTexID = GetTexture("Assets/Texture/noneTexture.png")->GetTextureID();

	// �f�v�X�����_���[������
	mDepthMapRender = new DepthMap;
	const int DepthmapSize = 4096;
	mDepthMapRender->CreateShadowMap(DepthmapSize);

	// HDR�����_���[������
	mHDRRenderer = new HDRRenderer(mScreenWidth, mScreenHeight, 4);

	// �J�����O
	glFrontFace(GL_CCW);
	glEnable(GL_FRONT_FACE);

	//�X�v���C�g�p�̒��_�z����쐬
	CreateSpriteVerts();

	CreateParticleVerts();

	CreateCubeVerts();

	// SDL_ttf�̏�����
	if (TTF_Init() != 0)
	{
		SDL_Log("Failed to initialize SDL_ttf");
		return false;
	}

	// �t�H���g�e�N�X�`���𐶐�
	CreateFontTexture(MFontTextureNum, MFontSize);

	// Effekseer������
	mEffekseerRenderer = ::EffekseerRendererGL::Renderer::Create(8000, EffekseerRendererGL::OpenGLDeviceType::OpenGL3);
	mEffekseerManager = ::Effekseer::Manager::Create(8000);

	// �`�惂�W���[���쐬
	mEffekseerManager->SetSpriteRenderer(mEffekseerRenderer->CreateSpriteRenderer());
	mEffekseerManager->SetRibbonRenderer(mEffekseerRenderer->CreateRibbonRenderer());
	mEffekseerManager->SetRingRenderer(mEffekseerRenderer->CreateRingRenderer());
	mEffekseerManager->SetTrackRenderer(mEffekseerRenderer->CreateTrackRenderer());
	mEffekseerManager->SetModelRenderer(mEffekseerRenderer->CreateModelRenderer());

	// Effekseer�p�̃e�N�X�`���E���f���E�}�e���A�����[�_�[
	mEffekseerManager->SetTextureLoader(mEffekseerRenderer->CreateTextureLoader());
	mEffekseerManager->SetModelLoader(mEffekseerRenderer->CreateModelLoader());
	mEffekseerManager->SetMaterialLoader(mEffekseerRenderer->CreateMaterialLoader());

	return true;
}

/// <summary>
/// �I������
/// </summary>
void Renderer::Shutdown()
{
	delete mSpriteVerts;
	mSpriteShader->Unload();
	delete mSpriteShader;
	mSkinnedDepthShader->Unload();
	delete mSkinnedDepthShader;
	mMeshShadowHDRShader->Unload();
	delete mMeshShadowHDRShader;
	mSkinnedShadowHDRShader->Unload();
	delete mSkinnedShadowHDRShader;
	delete mParticleVertex;
	mParticleShader->Unload();
	delete mParticleShader;
	delete mCubeVerts;
	mSkyBoxShader->Unload();
	delete mSkyBoxShader;

	// Effekseer�֘A�̔j��
	mEffekseerManager.Reset();
	mEffekseerRenderer.Reset();

	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
}

/// <summary>
/// ���[�h�����f�[�^�̉��
/// </summary>
void Renderer::UnloadData()
{
	// ���ׂẴe�N�X�`���̃f�[�^��j��
	for (auto i : mTextures)
	{
		i.second->Unload();
		delete i.second;
	}
	// ���ׂẴt�H���g�̃f�[�^��j��
	for (auto i : mFonts)
	{
		i.second->Unload();
		delete i.second;
	}
	// ���ׂẴ��b�V���̃f�[�^��j��
	for (auto i : mMeshes)
	{
		i.second->Unload();
		delete i.second;
	}
	// ���ׂẴX�P���g�����b�V���̃f�[�^��j��
	for (auto s : mSkeletons)
	{
		delete s.second;
	}
	// ���ׂẴA�j���[�V�����̃f�[�^��j��
	for (auto a : mAnims)
	{
		delete a.second;
	}
	// ���ׂẴG�t�F�N�g�̃f�[�^��j��
	for (auto e : mEffects)
	{
		delete e.second;
	}

	mTextures.clear();
	mFonts.clear();
	mMeshes.clear();
	mSkeletons.clear();
	mAnims.clear();
	mEffects.clear();
}

/// <summary>
/// �`�揈��
/// </summary>
void Renderer::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	// �f�v�X�����_�����O�p�X�J�n
	Matrix4 lightSpaceMat = mDepthMapRender->GetLightSpaceMatrix();
	mDepthMapRender->DepthRenderingBegin();
	{
		// �X�^�e�B�b�N���b�V����`��
		for (auto mc : mMeshComponents)
		{
			if (mc->GetVisible())
			{
				mc->Draw(mDepthMapRender->GetDepthMapShader());
			}
		}

		// �X�L�����b�V����`��
		mSkinnedDepthShader->SetActive();
		mSkinnedDepthShader->SetMatrixUniform("uLightSpaceMat", lightSpaceMat);
		// �X�L���V�F�[�_�Ƀp�����[�^�Z�b�g
		for (auto sk : mSkeletalMeshes)
		{
			if (sk->GetVisible())
			{
				sk->Draw(mSkinnedDepthShader);
			}
		}
	}
	// �f�v�X�����_�����O�p�X�I��
	mDepthMapRender->DepthRenderignEnd();

	mHDRRenderer->HdrRecordBegin();
	{
		// �X�J�C�{�b�N�X�`��
		if (mActiveSkyBox != nullptr)
		{
			mSkyBoxShader->SetActive();
			// �Q�[���̋�Ԃɍ��킹�邽�߂̃I�t�Z�b�g�s����Z�b�g
			Matrix4 offset = Matrix4::CreateRotationX(Math::ToRadians(90.0f));
			mSkyBoxShader->SetMatrixUniform("u_offset", offset);

			// Uniform�ɋt�s����Z�b�g
			Matrix4 InvView = mView;
			InvView.Invert();
			InvView.Transpose();
			mSkyBoxShader->SetMatrixUniform("u_invView", InvView);
			mSkyBoxShader->SetMatrixUniform("u_projection", mProjection);
			mSkyBoxShader->SetIntUniform("u_skybox", 0);

			mActiveSkyBox->Draw(mSkyBoxShader);
		}

		//�V���h�E�t���Ń��b�V����`��
		mMeshShadowHDRShader->SetActive();
		mMeshShadowHDRShader->SetMatrixUniform("uViewProj", mView * mProjection);
		mMeshShadowHDRShader->SetMatrixUniform("uLightSpaceMat", lightSpaceMat);
		mMeshShadowHDRShader->SetIntUniform("uTexture", 0);

		// �f�v�X�}�b�v���Z�b�g
		mMeshShadowHDRShader->SetIntUniform("depthMap", 4);// ���C�e�B���O�ϐ����Z�b�g
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, mDepthMapRender->GetDepthTexID());

		SetLightUniforms(mMeshShadowHDRShader, mView);

		// �S�Ẵ��b�V���R���|�[�l���g��`��
		for (auto mc : mMeshComponents)
		{
			if (mc->GetVisible())
			{
				mc->Draw(mMeshShadowHDRShader);
			}
		}

		// �X�L�����V���h�E���b�V��
		mSkinnedShadowHDRShader->SetActive();
		// �r���[�v���W�F�N�V���������C�g��ԍs��Z�b�g
		mSkinnedShadowHDRShader->SetMatrixUniform("uViewProj", mView * mProjection);
		mSkinnedShadowHDRShader->SetMatrixUniform("uLightSpaceMat", lightSpaceMat);
		mSkinnedShadowHDRShader->SetIntUniform("uTexture", 0);
		mSkinnedShadowHDRShader->SetIntUniform("depthMap", 4);

		// ���C�g�p�����[�^�̃Z�b�g
		SetLightUniforms(mSkinnedShadowHDRShader, mView);

		for (auto sk : mSkeletalMeshes)
		{
			if (sk->GetVisible())
			{
				sk->Draw(mSkinnedShadowHDRShader);
			}
		}
	}
	mHDRRenderer->HdrRecordEnd();

	//////////////////////////////////////////////////////////////////
	// HDR Bloom �̍쐬������
	/////////////////////////////////////////////////////////////////
	mHDRRenderer->HiBrightBlurCreate();
	mHDRRenderer->HdrTonemapAndBrightBlurCombine();

	// HDRBuffer�Ƀ����_�����O�����Ƃ���Depth�����X�N���[���ɃR�s�[
	mHDRRenderer->CopyDepthToScreen();

	//�G�t�F�N�g�֘A
	mEffekseerRenderer->BeginRendering();
	mEffekseerManager->Draw();
	mEffekseerRenderer->EndRendering();

	// �����蔻��f�o�b�OBox�̕\��
	PHYSICS->DebugShowBox();

	DrawParticle();

	// UI�̕`��
	//�A���t�@�u�����f�B���O��L���ɂ���
	glEnable(GL_BLEND);
	//�f�v�X�o�b�t�@�@�𖳌��ɂ���
	glDisable(GL_DEPTH_TEST);

	// RGB�����ƃ������̃u�����f�B���O���@��ʁX�ɐݒ�
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	// RGB�����ƃA���t�@�����ɕʁX�̍����W����ݒ�
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	// �X�v���C�g�V�F�[�_�[���A�N�e�B�u�ɂ���/�X�v���C�g���_�z���L���ɂ���
	mSpriteShader->SetActive();
	mSpriteVerts->SetActive();
	// ���ׂẴX�v���C�g�̕`��
	for (auto sprite : mSprites)
	{
		if (sprite->GetVisible())
		{
			sprite->Draw(mSpriteShader);
		}
	}

	// �o�b�t�@������
	SDL_GL_SwapWindow(mWindow);
}

/// <summary>
/// �S�Ẵp�[�e�B�N����`�揀��
/// </summary>
void Renderer::DrawParticle()
{
	std::sort(mParticles.begin(), mParticles.end(), std::greater<ParticleComponent*>());

 	if (mParticles.size() == 0)
	{
		return;
	}
	// �u�����h���[�h������Ԏ擾
	ParticleComponent::ParticleBlendType blendType, prevType;
	auto itr = mParticles.begin();
	blendType = prevType = (*itr)->GetBlendType();

	// �e�N�X�`��ID������Ԏ擾
	int nowTexture, prevTexture;
	nowTexture = prevTexture = (*itr)->GetTexture()->GetTextureID();

	// �r���[�v���W�F�N�V�����s��
	Matrix4 viewProjectionMat;
	viewProjectionMat = mView * mProjection;

	// �V�F�[�_�[ON
	mParticleShader->SetActive();
	mParticleShader->SetMatrixUniform("uViewProj", viewProjectionMat);

	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);

	// ���ׂẴp�[�e�B�N����`��
	ChangeBlendMode(blendType);
	ChangeTexture(nowTexture);

	for (auto particle : mParticles)
	{
		if (particle->GetVisible())
		{
			//�u�����h���[�h�ύX���K�v�Ȃ�ύX����
			blendType = particle->GetBlendType();
			blendType = particle->GetBlendType();
			if (blendType != prevType)
			{
				ChangeBlendMode(blendType);
			}
			// �e�N�X�`���ύX���K�v�Ȃ�ύX����
			nowTexture = particle->GetTexture()->GetTextureID();
			if (nowTexture != prevTexture)
			{
				ChangeTexture(nowTexture);
			}

			// �p�[�e�B�N���`��
			particle->Draw(mParticleShader);

			// �O��`���ԂƂ��ĕۑ�
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

	// Effekseer �ɍ��W�n�����킹�čs����Z�b�g����
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

	// Effekseer �ɍ��W�n�����킹�čs����Z�b�g����
	Matrix4 tmp = proj;
	tmp.mat[2][2] *= -1;
	tmp.mat[2][3] *= -1;

	Effekseer::Matrix44 eProj;
	eProj = tmp;
	RENDERER->GetEffekseerRenderer()->SetProjectionMatrix(eProj);
}

void Renderer::SetDepthSetting(const Vector3& _CenterWorldPos, const Vector3& _LightDir, const Vector3& _UpVec, const float _LightDistance)
{
	mDepthMapRender->CalcLightSpaceMatrix(_CenterWorldPos, _LightDir, _UpVec, _LightDistance);
}

/// <summary>
/// �X�v���C�g�̒ǉ�
/// </summary>
/// <param name="_spriteComponent"> �ǉ�����SpriteComponent�N���X�̃|�C���^ </param>
void Renderer::AddSprite(SpriteComponent* _spriteComponent)
{
	// ������X�v���C�g����}������ꏊ�̌���
	// (DrawOrder�����������Ԃɕ`�悷�邽��)
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

	// ���������ꏊ��iter�̏ꏊ�ɑ}��
	mSprites.insert(iter, _spriteComponent);
}

/// <summary>
/// �X�v���C�g�̍폜
/// </summary>
/// <param name="_spriteComponent"> �폜����SpriteComponent�N���X�̃|�C���^ </param>
void Renderer::RemoveSprite(SpriteComponent* _spriteComponent)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), _spriteComponent);
	mSprites.erase(iter);
}

/// <summary>
/// �p�[�e�B�N���̒ǉ�
/// </summary>
/// <param name="_particleComponent"> �ǉ�����ParticleObject�N���X�̃|�C���^ </param>
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
/// �p�[�e�B�N���̍폜
/// </summary>
/// <param name="_particleComponent"> �폜����ParticleObject�N���X�̃|�C���^ </param>
void Renderer::RemoveParticle(ParticleComponent * _particleComponent)
{
	auto iter = std::find(mParticles.begin(), mParticles.end(), _particleComponent);
	mParticles.erase(iter);
}

/// <summary>
/// ���b�V���R���|�[�l���g�̒ǉ�
/// </summary>
/// <param name="_meshComponent"> �ǉ�����MeshComponent�N���X�̃|�C���^ </param>
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
/// ���b�V���R���|�[�l���g�̍폜
/// </summary>
/// <param name="_meshComponent"> �폜����MeshComponent�N���X�̃|�C���^ </param>
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
/// �X�P���g�����f�����擾
/// </summary>
/// <param name="_FileName"> �擾�������X�P���g�����f���̃t�@�C���� </param>
/// <returns> �X�P���g���N���X�̃|�C���^ </returns>
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
/// �X�P���g���A�j���[�V�������擾
/// </summary>
/// <param name="_FileName"> �擾�������X�P���g���A�j���[�V�����̃t�@�C���� </param>
/// <param name="_Loop"> �A�j���[�V���������[�v�����邩 </param>
/// <returns> �A�j���[�V�����N���X�̃|�C���^ </returns>
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
/// �e�N�X�`�����擾
/// </summary>
/// <param name="_FileName"> �擾�������e�N�X�`���̃t�@�C���� </param>
/// <returns> �e�N�X�`���N���X�̃|�C���^ </returns>
Texture* Renderer::GetTexture(const std::string& _FileName)
{
	Texture* texture = nullptr;
	//���łɍ쐬����ĂȂ������ׂ�
	auto itr = mTextures.find(_FileName);
	if (itr != mTextures.end())
	{
		texture = itr->second;
	}
	//�쐬�ς݂łȂ��ꍇ�A�V�����e�N�X�`�����쐬
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
/// ���b�V�����擾
/// </summary>
/// <param name="_FileName"> �擾���������b�V���̃t�@�C���� </param>
/// <returns> ���b�V���N���X�̃|�C���^ </returns>
Mesh* Renderer::GetMesh(const std::string& _FileName)
{
	Mesh* m = nullptr;
	//���łɍ쐬����ĂȂ������ׂ�
	auto iter = mMeshes.find(_FileName);
	if (iter != mMeshes.end())
	{
		m = iter->second;
	}
	//�쐬�ς݂łȂ��ꍇ�A�V�������b�V�����쐬
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
/// �V�F�[�_�[�̓ǂݍ���
/// </summary>
/// <returns> true : ���� , false : ���s </returns>
bool Renderer::LoadShaders()
{
	// �X�v���C�g�V�F�[�_�[�̍쐬
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}

	mSpriteShader->SetActive();
	// �r���[�s��̐ݒ�
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(mScreenWidth, mScreenHeight);
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);

	//// ���b�V���V�F�[�_�[�̍쐬
	//mMeshShader = new Shader();
	//if (!mMeshShader->Load("Shaders/Phong.vert", "Shaders/ShadowHDRMesh.frag"))
	//{
	//	return false;
	//}

	//// ���b�V��
	//mMeshShader->SetActive();

	// ���b�V���̃V���h�E�V�F�[�_�[
	mMeshShadowHDRShader = new Shader();
	if (!mMeshShadowHDRShader->Load("Shaders/ShadowMesh.vert", "Shaders/ShadowHDRMesh.frag"))
	{
		return false;
	}

	//// �X�L�����b�V���V�F�[�_�[
	//mSkinnedShader = new Shader();
	//if (!mSkinnedShader->Load("Shaders/Skinned.vert", "Shaders/Phong.frag"))
	//{
	//	return false;
	//}
	//mSkinnedShader->SetActive();
	//mSkinnedShader->SetMatrixUniform("uViewProj", mView * mProjection);

	// �X�L�����b�V���̃f�v�X�V�F�[�_�[
	mSkinnedDepthShader = new Shader();
	if (!mSkinnedDepthShader->Load("Shaders/SkinnedDepth.vert", "Shaders/Depthmap.frag"))
	{
		return false;
	}

	// �X�L�����b�V���̃V���h�E�V�F�[�_�[
	mSkinnedShadowHDRShader = new Shader;
	if (!mSkinnedShadowHDRShader->Load("Shaders/SkinnedShadow.vert", "Shaders/ShadowHDRMesh.frag"))
	{
		return false;
	}

	// �p�[�e�B�N���V�F�[�_�[
	mParticleShader = new Shader();
	if (!mParticleShader->Load("Shaders/Phong.vert", "Shaders/Particle.frag"))
	{
		printf("�V�F�[�_�[�ǂݍ��ݎ��s\n");
	}

	// �X�J�C�{�b�N�X�V�F�[�_�[�̍쐬
	mSkyBoxShader = new Shader();
	if (!mSkyBoxShader->Load("Shaders/gBuffer_SkyBox.vert", "Shaders/gBuffer_SkyBox.frag"))
	{
		return false;
	}

	return true;
}

/// <summary>
/// �X�v���C�g�p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
/// </summary>
void Renderer::CreateSpriteVerts()
{
	float vertices[] = {
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // ����
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // �E��
		0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // �E��
		0.0f,-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f  // ����
	};

	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}

/// <summary>
/// �p�[�e�B�N���p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
/// </summary>
void Renderer::CreateParticleVerts()
{
	float vertices[] = {
		 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // top left
		 0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top right
		 0.5f, 0.0f,-0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // bottom right
		 0.0f, 0.0f,-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f  // bottom left
	};

	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};
	mParticleVertex = new VertexArray(vertices, 4, VertexArray::PosNormTex, indices, 6);
}

/// <summary>
/// �L���[�u�}�b�v(�X�J�C�{�b�N�X�p)���_�z���`
/// </summary>
void Renderer::CreateCubeVerts()
{
	mCubeVerts = new VertexArray();
	mCubeVerts->CreateCubeVerts();
}

/// <summary>
/// �p�[�e�B�N���̒��_�z���ݒ�
/// </summary>
void Renderer::SetParticleVertex()
{
	mParticleVertex->SetActive();
}

/// <summary>
/// �t�H���g�e�N�X�`���̐���
/// </summary>
/// <param name="_Value"> �e�N�X�`���̖��� </param>
/// <param name="_FontSize"> �t�H���g�T�C�Y </param>
void Renderer::CreateFontTexture(const int& _Value, const int& _FontSize)
{
	// �t�H���g�̐���
	Font* font = GetFont("Assets/Font/msmincho.ttc");

	// �v�f�������킹���e�N�X�`���̖���
	int numTexture = _Value + 1;

	// �i�[����ϒ��z������T�C�Y
	mFontTextures.resize(numTexture);

	// �t�H���g�e�N�X�`�����w�肵��������������
	for (int i = 0; i < numTexture; i++)
	{
		std::string str;
		str = std::to_string(i);
		mFontTextures[i] = font->RenderText(str, Color::White, _FontSize);
	}

	std::string str = "/ 10";
	mFontTextures.push_back(font->RenderText(str, Color::White, _FontSize));
	str = "/ 50";
	mFontTextures.push_back(font->RenderText(str, Color::White, _FontSize));
}

/// <summary>
/// ���������V�F�[�_�[�̕ϐ��ɃZ�b�g����
/// </summary>
/// <param name="_shader"> �Z�b�g����Shader�N���X�̃|�C���^ </param>
/// <param name="_View"> �r���[�s�� </param>
void Renderer::SetLightUniforms(Shader* _shader, const Matrix4& _View)
{
	// �r���[�s����t�s��ɂ���
	Matrix4 invView = _View;
	invView.Invert();
	_shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
	// �����̐ݒ�
	_shader->SetVectorUniform("uAmbientLight", mAmbientLight);
	// ���s�����̐ݒ�
	_shader->SetVectorUniform("uDirLight.mDirection",
		mDirLight.m_direction);
	_shader->SetVectorUniform("uDirLight.mDiffuseColor",
		mDirLight.m_diffuseColor);
	_shader->SetVectorUniform("uDirLight.mSpecColor",
		mDirLight.m_specColor);
}

/// <summary>
/// �G�t�F�N�g���擾
/// </summary>
/// <param name="_FileName"> �擾�������G�t�F�N�g�̃t�@�C���� </param>
/// <returns> �G�t�F�N�g�N���X�̃|�C���^ </returns>
EffekseerEffect* Renderer::GetEffect(const char16_t* _FileName)
{
	// �G�t�F�N�g�t�@�C������x�ǂݍ��񂾂����m�F
	EffekseerEffect* effect = nullptr;
	auto iter = mEffects.find(_FileName);

	// ��x�ǂ�ł���Ȃ�Ԃ�
	if (iter != mEffects.end())
	{
		return iter->second;
	}

	//�ǂ�ł��Ȃ���ΐV�K�ǉ�
	effect = new EffekseerEffect;
	if (effect->LoadEffect(_FileName))
	{
		mEffects.emplace(_FileName, effect);
	}
	else
	{
		delete effect;
		effect = nullptr;
	}
	return effect;
}


/// <summary>
/// �u�����h���[�h��ύX����
/// </summary>
/// <param name="_blendType"> �u�����h���[�h </param>
void Renderer::ChangeBlendMode(ParticleComponent::ParticleBlendType blendType)
{
	switch (blendType)
	{
	case ParticleComponent::eParticleBlendAdd:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);  //���Z����
		break;
	case ParticleComponent::eParticleBlendAlpha:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // �A���t�@�u�����h
		break;
	case ParticleComponent::eParticleBlendMult:
		glBlendFunc(GL_ZERO, GL_SRC_COLOR); //��Z����
		break;
	default:
		break;
	}
}

/// <summary>
/// �e�N�X�`����ύX
/// </summary>
/// <param name="_ChangeTextureID"> �e�N�X�`��ID </param>
void Renderer::ChangeTexture(const int& _ChangeTextureID)
{
	glBindTexture(GL_TEXTURE_2D, _ChangeTextureID);
}

/// <summary>
/// ���[���h���W�ł̃J�����ʒu�Z�o
/// </summary>
/// <returns> �J�����ʒu(���[���h���W) </returns>
Vector3 Renderer::CalcCameraPos()
{
	// �r���[�s���胏�[���h�ł̃J�����ʒu�Z�o
	Matrix4 transMat = mView;

	// �r���[�s��̈ړ������������
	Vector3 v;
	v.x = -1.0f * mView.mat[3][0];
	v.y = -1.0f * mView.mat[3][1];
	v.z = -1.0f * mView.mat[3][2];

	//�ړ���������菜�������Ɠ]�u���āA��]�����̋t�ϊ������
	transMat.mat[3][0] = transMat.mat[3][1] = transMat.mat[3][2] = 0.0f;
	transMat.Transpose();

	return Vector3(Vector3::Transform(v, transMat));
}

/// <summary>
/// �t�H���g���擾
/// </summary>
/// <param name="_FileName"> �擾�������t�H���g�̃t�@�C����  </param>
/// <returns> �t�H���g�N���X�̃|�C���^ </returns>
Font* Renderer::GetFont(const std::string& _FileName)
{
	Font* font = nullptr;
	//���łɍ쐬����ĂȂ������ׂ�
	auto itr = mFonts.find(_FileName);
	if (itr != mFonts.end())
	{
		font = itr->second;
	}
	//�쐬�ς݂łȂ��ꍇ�A�V�����t�H���g���쐬
	else
	{
		font = new Font();
		if (font->Load(_FileName))
		{
			mFonts.emplace(_FileName, font);
		}
		else
		{
			delete font;
			font = nullptr;
		}
	}

	return font;
}

/// <summary>
/// �t�H���g�e�N�X�`�����擾
/// </summary>
/// <param name="_FontDataNum"> �t�H���g�e�N�X�`���z��̗v�f�� </param>
/// <returns> �e�N�X�`���N���X�̃|�C���^ </returns>
Texture* Renderer::GetFontTexture(const int& _FontDataNum)
{
	return mFontTextures[_FontDataNum];
}