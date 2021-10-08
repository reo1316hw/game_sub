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
@brief  �C���X�^���X���쐬����
*/
void Renderer::CreateInstance()
{
	if (mRenderer == nullptr)
	{
		mRenderer = new Renderer();
	}
}

/*
@brief  �C���X�^���X���폜����
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
@brief  ����������
@return true : ���� , false : ���s
*/
bool Renderer::Initialize(float _ScreenWidth, float _screenHeight, bool _fullScreen)
{
	mScreenWidth = _ScreenWidth;
	mScreenHeight = _screenHeight;

	// OpenGL�̊e������ݒ肷��
	// �R�AOpenGL�v���t�@�C�����g��
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// OpenGL�̎g�p�o�[�W������3.3�Ɏw��
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
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

	// HDR�����_���[������
	mHDRRenderer = new HDRRenderer(mScreenWidth, mScreenHeight, 4);

	////// �J�����O
	//glFrontFace(GL_CCW);
	//glEnable(GL_FRONT_FACE);

	//�X�v���C�g�p�̒��_�z����쐬
	CreateSpriteVerts();

	CreateParticleVerts();

	// UI�̏������W�ɉ��Z�������W
	mAddPosition = Vector2::Zero;

	return true;
}

/*
@brief  �I������
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
@brief  ���[�h�����f�[�^�̉��
*/
void Renderer::UnloadData()
{
	// ���ׂẴe�N�X�`���̃f�[�^�����
	for (auto i : mTextures)
	{
		i.second->Unload();
		delete i.second;
	}
	mTextures.clear();

	// ���ׂẴ��b�V���̃f�[�^�����
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
@brief  �`�揈��
*/
void Renderer::Draw()
{

	mHDRRenderer->HdrRecordBegin();
	{
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

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);

		// ���b�V���R���|�[�l���g�̕`��
		// ��{�I�ȃ��b�V���V�F�[�_�[���A�N�e�B�u�ɂ���
		mMeshShader->SetActive();
		// �r���[�ˉe�s����X�V����
		mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);
		// �V�F�[�_�[�ɓn�����C�e�B���O�����X�V����
		SetLightUniforms(mMeshShader, mView);
		// ���ׂẴ��b�V���̕`��
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
	// HDR Bloom �̍쐬������
	/////////////////////////////////////////////////////////////////
	mHDRRenderer->HiBrightBlurCreate();
	mHDRRenderer->HdrTonemapAndBrightBlurCombine();

	// HDRBuffer�Ƀ����_�����O�����Ƃ���Depth�����X�N���[���ɃR�s�[
	mHDRRenderer->CopyDepthToScreen();

	// �����蔻��f�o�b�OBox�̕\��
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


	//// UI�̕`��
	//// �A���t�@�u�����f�B���O��L���ɂ���
	//glEnable(GL_BLEND);
	//// �f�v�X�o�b�t�@�@�𖳌��ɂ���
	//glDisable(GL_DEPTH_TEST);
	//// RGB�����ƃ������̃u�����f�B���O���@��ʁX�ɐݒ�
	//glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	//// RGB�����ƃA���t�@�����ɕʁX�̍����W����ݒ�
	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	//// UI�V�F�[�_�[���A�N�e�B�u�ɂ���/�X�v���C�g���_�z���L���ɂ���
	//mUiShader->SetActive();
	//mUiVerts->SetActive();
	//// ���ׂĂ�UI�̕`��
	//for (auto ui : mUis)
	//{
	//	if (ui->GetVisible())
	//	{
	//		ui->Draw(mUiShader, ui->GetOwner()->GetPosition());
	//	}
	//}

		// �o�b�t�@������
	SDL_GL_SwapWindow(mWindow);
}

/*
@brief  �X�v���C�g�̒ǉ�
@param	_spriteComponent�@�ǉ�����SpriteComponent�N���X�̃|�C���^
*/
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

/*
@brief �X�v���C�g�̍폜
@param	_spriteComponent�@�폜����SpriteComponent�N���X�̃|�C���^
*/
void Renderer::RemoveSprite(SpriteComponent* _spriteComponent)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), _spriteComponent);
	mSprites.erase(iter);
}

void Renderer::AddUI(UIComponent* _ui)
{
	// ������X�v���C�g����}������ꏊ�̌���
	// (DrawOrder�����������Ԃɕ`�悷�邽��)
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

	// ���������ꏊ��iter�̏ꏊ�ɑ}��
	mUis.insert(iterUi, _ui);
}

void Renderer::RemoveUI(UIComponent* _ui)
{
	auto iterUi = std::find(mUis.begin(), mUis.end(), _ui);
	mUis.erase(iterUi);
}

/*
@brief  �p�[�e�B�N���̒ǉ�
@param	_particleComponent�@�ǉ�����ParticleObject�N���X�̃|�C���^
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
@brief  �X�v���C�g�̍폜
@param	�폜����ParticleObject�N���X�̃|�C���^
*/
void Renderer::RemoveParticle(ParticleComponent * _particleComponent)
{
	auto iter = std::find(mParticles.begin(), mParticles.end(), _particleComponent);
	mParticles.erase(iter);
}

/*
@brief  ���b�V���R���|�[�l���g�̒ǉ�
@param	_meshComponent�@�ǉ�����MeshComponent�N���X�̃|�C���^
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
@brief  ���b�V���R���|�[�l���g�̍폜
@param	_meshComponent�@�폜����MeshComponent�N���X�̃|�C���^
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
@brief  �C���r�W�u�����b�V���R���|�[�l���g�̒ǉ�
@param	_invisibleMeshComponent�@�ǉ�����InvisibleMeshComponent�N���X�̃|�C���^
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
@brief  �C���r�W�u�����b�V���R���|�[�l���g�̍폜
@param	_invisibleMeshComponent�@�폜����InvisibleMeshComponent�N���X�̃|�C���^
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
@param _fileName ���f���ւ̃A�h���X
@return �X�P���g�����f���̎擾
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
@param _fileName �A�j���[�V�����ւ̃A�h���X
@return �X�P���g���A�j���[�V�����̎擾
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
@brief  �e�N�X�`���̎擾
@param	_fileName�@�擾�������e�N�X�`���̃t�@�C����
@return Texture�N���X�̃|�C���^
*/
Texture* Renderer::GetTexture(const std::string& _fileName)
{
	Texture* texture = nullptr;
	//���łɍ쐬����ĂȂ������ׂ�
	auto itr = mTextures.find(_fileName);
	if (itr != mTextures.end())
	{
		texture = itr->second;
	}
	//�쐬�ς݂łȂ��ꍇ�A�V�����e�N�X�`�����쐬
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
@brief  ���b�V���̎擾
@param	_fileName �擾���������b�V���̃t�@�C����
@return Mesh�N���X�̃|�C���^
*/
Mesh* Renderer::GetMesh(const std::string& _fileName)
{
	Mesh* m = nullptr;
	//���łɍ쐬����ĂȂ������ׂ�
	auto iter = mMeshes.find(_fileName);
	if (iter != mMeshes.end())
	{
		m = iter->second;
	}
	//�쐬�ς݂łȂ��ꍇ�A�V�������b�V�����쐬
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
@brief  �V�F�[�_�[�̓ǂݍ���
@return true : ���� , false : ���s
*/
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

	// UI�V�F�[�_�[�̍쐬
	mUiShader = new Shader();
	if (!mUiShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}

	mUiShader->SetActive();
	// �r���[�s��̐ݒ�
	Matrix4 viewUiProj = Matrix4::CreateSimpleViewProj(mScreenWidth, mScreenHeight);
	mUiShader->SetMatrixUniform("uViewProj", viewUiProj);

	// �W���̃��b�V���V�F�[�_�[�̍쐬
	mMeshShader = new Shader();
	if (!mMeshShader->Load("Shaders/Phong.vert", "Shaders/HDRMesh.frag"))
	{
		return false;
	}

	// �C���r�W�u�����b�V���V�F�[�_�[�̍쐬
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
		printf("�V�F�[�_�[�ǂݍ��ݎ��s\n");
	}

	mSkinnedShader = new Shader();
	if (!mSkinnedShader->Load("Shaders/Skinned.vert", "Shaders/Phong.frag"))
	{
		return false;
	}
	mSkinnedShader->SetActive();
	mSkinnedShader->SetMatrixUniform("uViewProj", mView * mProjection);

	// ���b�V��
	mMeshShader->SetActive();

	// �C���r�W�u�����b�V��
	mInvisibleMeshShader->SetActive();

	// �r���[�s��̐ݒ�
	mView = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
	mProjection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(90.0f),
		mScreenWidth, mScreenHeight, 10.0f, 10000.0f);

	mInvisibleMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);

	mBasicShader->SetActive();
	mBasicShader->SetMatrixUniform("uViewProj", mView * mProjection);
	return true;
}

/*
@brief  Sprite�p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
*/
void Renderer::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // ����
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // �E��
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // �E��
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // ����
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
	mUiVerts = new VertexArray(vertices, 4, indices, 6);
}

// �p�[�e�B�N�����_�쐬
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
	// �u�����h���[�h������Ԏ擾
	ParticleComponent::PARTICLE_BLEND_ENUM blendType, prevType;
	auto itr = mParticles.begin();
	blendType = prevType = (*itr)->GetBlendType();

	// �e�N�X�`��ID������Ԏ擾
	int nowTexture, prevTexture;
	nowTexture = prevTexture = (*itr)->GetTextureID();

	// �r���[�v���W�F�N�V�����s��
	Matrix4 viewProjectionMat;
	viewProjectionMat = mView * mProjection;

	// �V�F�[�_�[ON
	mParticleShader->SetActive();
	mParticleShader->SetMatrixUniform("uViewProj", viewProjectionMat);

	// �S�Ẵp�[�e�B�N���̃r���{�[�h�s����Z�b�g
	Matrix4 tmp;
	tmp = Matrix4::CreateRotationX(-0.5f * 3.14159f);
	(*itr)->SetBillboardMat(tmp);

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
			nowTexture = particle->GetTextureID();
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
//	// �e�N�X�`���̕��E�����ŃX�P�[�����O
//	Matrix4 scaleMat = Matrix4::CreateScale(
//		static_cast<float>(texture->GetWidth()) * scale,
//		static_cast<float>(texture->GetHeight()) * scale,
//		1.0f);
//	// �X�N���[���ʒu�̕��s�ړ�
//	Matrix4 transMat = Matrix4::CreateTranslation(
//		Vector3(offset.x - (mScreenWidth * 0.5f),
//			(mScreenHeight * 0.5f) - offset.y, 0.0f));
//	// ���[���h�ϊ�
//	Matrix4 world = scaleMat * transMat;
//	mSpriteShader->SetMatrixUniform("uWorldTransform", world);
//	mSpriteShader->SetFloatUniform("alpha", alpha);
//	// �e�N�X�`���Z�b�g
//	texture->SetActive();
//	// �l�p�`�`��
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
//
//}

//void Renderer::DrawTexture(Texture* texture, const Vector2& offset, float scale, float alpha)
//{
//	DrawTexture(texture, 0, 1, 1, offset, scale, alpha);
//}

/*
@brief  ���������V�F�[�_�[�̕ϐ��ɃZ�b�g����
@param _shader �Z�b�g����Shader�N���X�̃|�C���^
*/
void Renderer::SetLightUniforms(Shader* _shader, const Matrix4& _view)
{
	// �r���[�s����t�s��ɂ���
	Matrix4 invView = _view;
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

void Renderer::ChangeBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM blendType)
{
	switch (blendType)
	{
	case ParticleComponent::PARTICLE_BLEND_ENUM_ADD:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);  //���Z����
		break;
	case ParticleComponent::PARTICLE_BLEND_ENUM_ALPHA:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // �A���t�@�u�����h
		break;
	case ParticleComponent::PARTICLE_BLEND_ENUM_MULT:
		glBlendFunc(GL_ZERO, GL_SRC_COLOR); //��Z����
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
