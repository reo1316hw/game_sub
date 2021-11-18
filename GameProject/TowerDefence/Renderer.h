#pragma once
#include <SDL.h>
#include <unordered_map>
#include <vector>
#include <string>
#include "Math.h"
#include "ParticleComponent.h"

#define RENDERER Renderer::GetInstance()

// �O���錾
class EffekseerEffect;

/// <summary>
/// ���s�����p�̍\����
/// </summary>
struct DirectionalLight
{
	// ���̕���
	Vector3 m_direction;
	// �g�U���ːF
	Vector3 m_diffuseColor;
	// ���ʔ��ːF
	Vector3 m_specColor;
};

/// <summary>
/// �e�N�X�`���X�e�[�W
/// </summary>
enum class TextureStage
{
	DiffuseMap,
	NormalMap,
	SpecularMap,
	EmissiveMap,
	ShadowMap,
};

// �O���錾
class SpriteComponent;
class Texture;
class Mesh;
class Game;
class MeshComponent;
class InvisibleMeshComponent;
class Shader;
class VertexArray;
class ParticleComponent;
class HDRRenderer;
class CubeMapComponent;
class PlayerObject;
class EffekseerEffect;

/// <summary>
/// �`��̐i�s���s���N���X
/// </summary>
class Renderer
{
public:

	/// <summary>
	/// �C���X�^���X���쐬����
	/// </summary>
	static void CreateInstance();

	/// <summary>
	/// �C���X�^���X���폜����
	/// </summary>
	static void DeleteInstance();

	/*
	@brief  ����������
	@return true : ���� , false : ���s
	*/

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="_ScreenWidth"> �X�N���[���̕� </param>
	/// <param name="_ScreenHeight"> �X�N���[���̍��� </param>
	/// <param name="_IsFullScreen"> �t���X�N���[���ɂ��邩�̃t���O </param>
	/// <returns> true : ���� , false : ���s </returns>
	bool Initialize(const float& _ScreenWidth, const float& _ScreenHeight, const bool& _IsFullScreen);
	
	/// <summary>
	/// �I������
	/// </summary>
	void Shutdown();

	/// <summary>
	/// ���[�h�����f�[�^�̉��
	/// </summary>
	void UnloadData();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// �X�v���C�g�̒ǉ�
	/// </summary>
	/// <param name="_spriteComponent"> �ǉ�����SpriteComponent�N���X�̃|�C���^ </param>
	void AddSprite(SpriteComponent* _spriteComponent);

	/// <summary>
	/// �X�v���C�g�̍폜
	/// </summary>
	/// <param name="_spriteComponent"> �폜����SpriteComponent�N���X�̃|�C���^ </param>
	void RemoveSprite(SpriteComponent* _spriteComponent);

	/// <summary>
	/// �p�[�e�B�N���̒ǉ�
	/// </summary>
	/// <param name="_particleComponent"> �ǉ�����ParticleObject�N���X�̃|�C���^ </param>
	void AddParticle(ParticleComponent* _particleComponent);

	/// <summary>
	/// �p�[�e�B�N���̍폜
	/// </summary>
	/// <param name="_particleComponent"> �폜����ParticleObject�N���X�̃|�C���^ </param>
	void RemoveParticle(ParticleComponent* _particleComponent);

	/// <summary>
	/// ���b�V���R���|�[�l���g�̒ǉ�
	/// </summary>
	/// <param name="_meshComponent"> �ǉ�����MeshComponent�N���X�̃|�C���^ </param>
	void AddMeshComponent(MeshComponent* _meshComponent);

	/// <summary>
	/// ���b�V���R���|�[�l���g�̍폜
	/// </summary>
	/// <param name="_meshComponent"> �폜����MeshComponent�N���X�̃|�C���^ </param>
	void RemoveMeshComponent(MeshComponent* _meshComponent);

	/// <summary>
	/// �L���[�u�R���|�[�l���g�̍폜
	/// </summary>
	void RemoveCubeComponent() { mActiveSkyBox = nullptr; };

private:

	/// <summary>
	/// �R���X�g���N�^
	/// �B��
	/// </summary>
	Renderer();

	/// <summary>
	/// �f�X�g���N�^
	/// �B��
	/// </summary>
	~Renderer();

	/// <summary>
	/// �V�F�[�_�[�̓ǂݍ���
	/// </summary>
	/// <returns> true : ���� , false : ���s </returns>
	bool LoadShaders();

	/// <summary>
	/// �X�v���C�g�p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
	/// </summary>
	void CreateSpriteVerts();

	/// <summary>
	/// �p�[�e�B�N���p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
	/// </summary>
	void CreateParticleVerts();

	/// <summary>
	/// �L���[�u�}�b�v(�X�J�C�{�b�N�X�p)���_�z���`
	/// </summary>
	void CreateCubeVerts();

	/// <summary>
    /// �t�H���g�e�N�X�`���̐���
    /// </summary>
    /// <param name="_Value"> �e�N�X�`���̖��� </param>
    /// <param name="_FontSize"> �t�H���g�T�C�Y </param>
	void CreateFontTexture(const int& _Value, const int& _FontSize);

	/// <summary>
	/// �S�Ẵp�[�e�B�N����`�揀��
	/// </summary>
	void DrawParticle();

	/// <summary>
	/// ���������V�F�[�_�[�̕ϐ��ɃZ�b�g����
	/// </summary>
	/// <param name="_shader"> �Z�b�g����Shader�N���X�̃|�C���^ </param>
	/// <param name="_View"> �r���[�s�� </param>
	void SetLightUniforms(Shader* _shader, const Matrix4& _View);

	/// <summary>
	/// �u�����h���[�h��ύX����
	/// </summary>
	/// <param name="_blendType"> �u�����h���[�h </param>
	void ChangeBlendMode(ParticleComponent::ParticleBlendType _blendType);

	/// <summary>
	/// �e�N�X�`����ύX
	/// </summary>
	/// <param name="_ChangeTextureID"> �e�N�X�`��ID </param>
	void ChangeTexture(const int& _ChangeTextureID);

	/// <summary>
	/// ���[���h���W�ł̃J�����ʒu�Z�o
	/// </summary>
	/// <returns> �J�����ʒu(���[���h���W) </returns>
	Vector3 CalcCameraPos();

	// �t�@�C�����ŃX�P���g�����擾���邽�߂̘A�z�z��
	std::unordered_map<std::string, Skeleton*> mSkeletons;
	// �t�@�C�����ŃA�j���[�V�������擾���邽�߂̘A�z�z��
	std::unordered_map<std::string, Animation*> mAnims;
	// �t�@�C�����Ń��b�V�����擾���邽�߂̘A�z�z��
	std::unordered_map<std::string, Mesh*> mMeshes;
	// �t�@�C�����Ńe�N�X�`�����擾���邽�߂̘A�z�z��
	std::unordered_map<std::string, Texture*>mTextures;
	// �t�@�C�����ŃG�t�F�N�g���擾���邽�߂̘A�z�z��
	std::unordered_map<const char16_t*, EffekseerEffect*> mEffects;
	// �t�@�C�����Ńt�H���g���擾���邽�߂̘A�z�z��
	std::unordered_map<std::string, class Font*> mFonts;

	// ���b�V���̕`��Ɏg���郁�b�V���R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
	std::vector<MeshComponent*> mMeshComponents;
	// �X�P���g�����b�V���̕`��Ɏg����X�P���g�����b�V���R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
	std::vector<SkeletalMeshComponent*> mSkeletalMeshes;
	// �X�v���C�g�̕`��Ɏg����X�v���C�g�R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
	std::vector<SpriteComponent*> mSprites;
	// �p�[�e�B�N���̕`��Ɏg����p�[�e�B�N���R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
	std::vector<ParticleComponent*> mParticles;
	// �t�H���g�̕`��Ɏg����e�N�X�`���̃|�C���^�̉ϒ��R���e�i
	std::vector<Texture*> mFontTextures;

	// �t�H���g�e�N�X�`���̖���(�g����������������)
	const int MFontTextureNum;
	// �t�H���g�̃T�C�Y
	const int MFontSize;

	// ���ݒ�e�N�X�`���̏ꍇ�Ɋ��蓖�Ă��鍕�F�e�N�X�`��
	unsigned int mUndefineTexID;

	// �X�N���[���̉���
	float mScreenWidth;
	// �X�N���[���̏c��
	float mScreenHeight;

	// ����
	Vector3 mAmbientLight;

	// �r���[�s��
	Matrix4 mView;
	// �ˉe�s��
	Matrix4 mProjection;
	// �r���{�[�h�s��
	Matrix4 mBillboardMat;
	
	// ���s����
	DirectionalLight mDirLight;
	// �E�B���h�E
	SDL_Window* mWindow;
	// �R���e�L�X�g
	SDL_GLContext mContext;

	// �����̃C���X�^���X
	static Renderer* mRenderer;

	// �����_���[�̏�Ԃ��܂ލ\���̂̃|�C���^
	SDL_Renderer* mSdlRenderer;
	// �X�v���C�g
	Shader* mSpriteShader;
	VertexArray* mSpriteVerts;
	// ���b�V��
	Shader* mMeshShader;
	// �X�L�����b�V��
	Shader*  mSkinnedShader;  
	// �p�[�e�B�N��
	Shader* mParticleShader;
	// �p�[�e�B�N���p���_��`
	VertexArray* mParticleVertex;
	// �X�J�C�{�b�N�X
	Shader* mSkyBoxShader;
	// �L���[�u���_�z��
	VertexArray* mCubeVerts;
	// �L����(�`�悷��)�L���[�u�}�b�v
	CubeMapComponent* mActiveSkyBox; 

	// �v���C���[
	PlayerObject* mPlayer;
	// HDR �����_���[
	HDRRenderer* mHDRRenderer;

	// Effekseer�֘A
	Effekseer::RefPtr<EffekseerRendererGL::Renderer> mEffekseerRenderer; // Effekseer�����_��
	Effekseer::RefPtr<Effekseer::Manager>            mEffekseerManager; // Effekseer�}�l�[�W��  

public:// �Q�b�^�[�Z�b�^�[

	/// <summary>
	/// �C���X�^���X���擾����
	/// </summary>
	/// <returns> Renderer�N���X�̃C���X�^���X </returns>
	static Renderer* GetInstance() { return mRenderer; }

	/// <summary>
	/// �e�N�X�`�����擾
	/// </summary>
	/// <param name="_FileName"> �擾�������e�N�X�`���̃t�@�C���� </param>
	/// <returns> �e�N�X�`���N���X�̃|�C���^ </returns>
	Texture* GetTexture(const std::string& _FileName);

	/// <summary>
	/// �t�H���g���擾
	/// </summary>
	/// <param name="_FileName"> �擾�������t�H���g�̃t�@�C���� </param>
	/// <returns> �t�H���g�N���X�̃|�C���^ </returns>
	Font* GetFont(const std::string& _FileName);

	/// <summary>
	/// �t�H���g�e�N�X�`�����擾
	/// </summary>
	/// <param name="_Number"> ���� </param>
	/// <returns> �e�N�X�`���N���X�̃|�C���^ </returns>
	Texture* GetFontTexture(const int& _Number);

	/// <summary>
	/// �X�P���g�����f�����擾
	/// </summary>
	/// <param name="_FileName"> �擾�������X�P���g�����f���̃t�@�C���� </param>
	/// <returns> �X�P���g���N���X�̃|�C���^ </returns>
	const Skeleton* GetSkeleton(const char* _FileName);

	/// <summary>
	/// �X�P���g���A�j���[�V�������擾
	/// </summary>
	/// <param name="_FileName"> �擾�������X�P���g���A�j���[�V�����̃t�@�C���� </param>
	/// <param name="_Loop"> �A�j���[�V���������[�v�����邩 </param>
	/// <returns> �A�j���[�V�����N���X�̃|�C���^ </returns>
	const Animation* GetAnimation(const char* _FileName, const bool& _Loop);

	/// <summary>
	/// ���b�V�����擾
	/// </summary>
	/// <param name="_FileName"> �擾���������b�V���̃t�@�C���� </param>
	/// <returns> ���b�V���N���X�̃|�C���^ </returns>
	Mesh* GetMesh(const std::string& _FileName);

	/// <summary>
	/// ������ݒ肷��
	/// </summary>
	/// <param name="_Ambient"> ���� </param>
	void SetAmbientLight(const Vector3& _Ambient) { mAmbientLight = _Ambient; }

	/// <summary>
	/// ���s�����̍\���̂��擾����
	/// </summary>
	/// <returns> ���s�����̍\���� </returns>
	DirectionalLight& GetDirectionalLight() { return mDirLight; }

	/// <summary>
	/// �X�N���[���̕����擾����
	/// </summary>
	/// <returns> �X�N���[���̕� </returns>
	float GetScreenWidth() const { return mScreenWidth; }

	/// <summary>
	/// �X�N���[���̍������擾����
	/// </summary>
	/// <returns> �X�N���[���̍��� </returns>
	float GetScreenHeight() const { return mScreenHeight; }

	/// <summary>
	/// �r���[�s����擾����
	/// </summary>
	/// <returns> �r���[�s�� </returns>
	Matrix4 GetViewMatrix() const { return mView; }

	/// <summary>
	/// �r���[�s���ݒ肷��
	/// </summary>
	/// <param name="_View"> �r���[�s�� </param>
	void SetViewMatrix(const Matrix4& _View);

	/// <summary>
	/// �v���W�F�N�V�����s����擾����
	/// </summary>
	/// <returns> �v���W�F�N�V�����s�� </returns>
	Matrix4 GetProjectionMatrix() { return mProjection; }

	void SetProjMatrix(const Matrix4& proj);// �v���W�F�N�V�����s��ɃZ�b�g

	/// <summary>
	/// �p�[�e�B�N���̒��_�z���ݒ�
	/// </summary>
	void SetParticleVertex();

	/// <summary>
	/// �����_���[�̏�Ԃ��܂ލ\���̂��擾
	/// </summary>
	/// <returns> �����_���[�̏�Ԃ��܂ލ\���̂̃|�C���^ </returns>
	SDL_Renderer* GetSDLRenderer() { return mSdlRenderer; }

	/// <summary>
	/// ���ݒ�e�N�X�`���̏ꍇ�Ɋ��蓖�Ă��鍕�F�e�N�X�`�����擾����
	/// </summary>
	/// <returns> ���ݒ�e�N�X�`���̏ꍇ�Ɋ��蓖�Ă��鍕�F�e�N�X�`�� </returns>
	unsigned int GetUndefineTexID() { return mUndefineTexID; }

	/// <summary>
	/// �X�J�C�{�b�N�X���A�N�e�B�u�ɂ���
	/// </summary>
	/// <param name="_activeSkyBox"> �L���[�u�}�b�v�̃|�C���^ </param>
	void SetActiveSkyBox(CubeMapComponent* _activeSkyBox) { mActiveSkyBox = _activeSkyBox; }

	/// <summary>
	/// �L���[�u�}�b�v�̒��_�z����擾����
	/// </summary>
	/// <returns> �L���[�u�}�b�v�̒��_�z�� </returns>
	VertexArray* GetCubeMapVerts() { return mCubeVerts; }

	/// <summary>
	/// �G�t�F�N�g���擾
	/// </summary>
	/// <param name="_FileName"> �擾�������G�t�F�N�g�̃t�@�C���� </param>
	/// <returns> �G�t�F�N�g�N���X�̃|�C���^ </returns>
	EffekseerEffect* GetEffect(const char16_t* _FileName);

	// Effekseer�֘A
	Effekseer::RefPtr<EffekseerRendererGL::Renderer> GetEffekseerRenderer() { return mEffekseerRenderer; }
	Effekseer::RefPtr<Effekseer::Manager> GetEffekseerManager() { return mEffekseerManager; }
};