#pragma once
#include <SDL.h>
#include <unordered_map>
#include <vector>
#include <string>
#include "Math.h"
#include "ParticleComponent.h"
#define RENDERER Renderer::GetInstance()

//���s�����p�̍\����
struct DirectionalLight
{
	// ���̕���
	Vector3 m_direction;
	// �g�U���ːF
	Vector3 m_diffuseColor;
	// ���ʔ��ːF
	Vector3 m_specColor;
};

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

/*
@file Renderer.h
@brief �`��̐i�s���s���N���X
*/
class Renderer
{
public:
	/*
	@brief  �C���X�^���X���擾����
	@return Renderer�N���X�̃C���X�^���X
	*/
	static Renderer* GetInstance() { return mRenderer; }

	/*
	@brief  �C���X�^���X���쐬����
	*/
	static void CreateInstance();

	/*
	@brief  �C���X�^���X���폜����
	*/
	static void DeleteInstance();

	/*
	@brief  ����������
	@return true : ���� , false : ���s
	*/
	bool Initialize(float _screenWidth, float _screenHeight, bool _fullScreen);
	/*
	@brief  �I������
	*/
	void Shutdown();

	/*
	@brief  ���[�h�����f�[�^�̉��
	*/
	void UnloadData();

	/*
	@brief  �`�揈��
	*/
	void Draw();

	/*void DrawTexture(class Texture* texture, const Vector2& offset = Vector2::Zero, float scale = 1.0f, float alpha = 1.0f);*/
	   
	/*
	@brief  �X�v���C�g�̒ǉ�
	@param	_spriteComponent�@�ǉ�����SpriteComponent�N���X�̃|�C���^
	*/
	void AddSprite(SpriteComponent* _spriteComponent);

	/*
	@brief �X�v���C�g�̍폜
	@param	_spriteComponent�@�폜����SpriteComponent�N���X�̃|�C���^
	*/
	void RemoveSprite(SpriteComponent* _spriteComponent);

	/*
	@brief  �p�[�e�B�N���̒ǉ�
	@param	_particleComponent�@�ǉ�����ParticleObject�N���X�̃|�C���^
	*/
	void AddParticle(ParticleComponent* _particleComponent);

	/*
	@brief  �X�v���C�g�̍폜
	@param	�폜����ParticleObject�N���X�̃|�C���^
	*/
	void RemoveParticle(ParticleComponent* _particleComponent);
	
	/*
	@brief  ���b�V���R���|�[�l���g�̒ǉ�
	@param	_meshComponent�@�ǉ�����MeshComponent�N���X�̃|�C���^
	*/
	void AddMeshComponent(MeshComponent* _meshComponent);

	/*
	@brief  ���b�V���R���|�[�l���g�̍폜
	@param	_meshComponent�@�폜����MeshComponent�N���X�̃|�C���^
	*/
	void RemoveMeshComponent(MeshComponent* _meshComponent);

	/*
	@brief  ���b�V���R���|�[�l���g�̒ǉ�
	@param	_meshComponent�@�ǉ�����MeshComponent�N���X�̃|�C���^
	*/
	void AddInvisibleMeshComponent(InvisibleMeshComponent* _invisibleMeshComponent);

	/*
	@brief  ���b�V���R���|�[�l���g�̍폜
	@param	_meshComponent�@�폜����MeshComponent�N���X�̃|�C���^
	*/
	void RemoveInvisibleMeshComponent(InvisibleMeshComponent* _invisibleMeshComponent);


	/*
	@brief  �e�N�X�`���̎擾
	@param	_fileName�@�擾�������e�N�X�`���̃t�@�C����
	@return Texture�N���X�̃|�C���^
	*/
	Texture* GetTexture(const std::string& _fileName);
	   
	/*
	@param _fileName ���f���ւ̃A�h���X
	@return �X�P���g�����f���̎擾
	*/
	const class Skeleton* GetSkeleton(const char* _fileName);                       
	/*
	@param _fileName �A�j���[�V�����ւ̃A�h���X
	@return �X�P���g���A�j���[�V�����̎擾
	*/
	const class Animation* GetAnimation(const char* _fileName, bool _loop);                     // �X�P���^���A�j���[�V�����̎擾

	/*
	@brief  ���b�V���̎擾
	@param	_fileName �擾���������b�V���̃t�@�C����
	@return Mesh�N���X�̃|�C���^
	*/
	Mesh* GetMesh(const std::string& _fileName);

	/*
	@brief	�r���[�s���ݒ肷��
	@param	_view �r���[�s��
	*/
	void SetViewMatrix(const Matrix4& _view) { mView = _view; }

	/*
	@brief	������ݒ肷��
	@param	_ambient Vector3�i������\���j
	*/
	void SetAmbientLight(const Vector3& _ambient) { mAmbientLight = _ambient; }

	/*
	@brief	���s�����̍\���̂��擾����
	@return	DirectionalLight�i���s�����̍\���́j
	*/
	DirectionalLight& GetDirectionalLight() { return mDirLight; }

	/*
	@brief	�X�N���[���̉������擾����
	@return	�X�N���[���̉���
	*/
	float GetScreenWidth() const { return mScreenWidth; }

	/*
	@brief	�X�N���[���̏c�����擾����
	@return	�X�N���[���̏c��
	*/
	float GetScreenHeight() const { return mScreenHeight; }

	Matrix4 GetViewMatrix() const { return mView; }

	void SetParticleVertex();

	Matrix4 GetProjectionMatrix() { return mProjection; }

	SDL_Renderer* GetSDLRenderer() { return mSdlRenderer; }

	unsigned int GetUndefineTexID() { return mUndefineTexID; }

	// �X�J�C�{�b�N�X���A�N�e�B�u�ɂ���
	void SetActiveSkyBox(CubeMapComponent* _activeSkyBox) { mActiveSkyBox = _activeSkyBox; }

	VertexArray* GetCubeMapVerts() { return mCubeVerts; }

	/*
    @brief �L���[�u�}�b�v(�X�J�C�{�b�N�X�p)���_�z���`
    */
	void CreateCubeVerts();

	/*void DrawTexture(Texture* texture, const Vector2& offset, float scale = 1.0f, float alpha = 1.0f);
	void DrawTexture(class Texture* texture, int index, int xDyvNum, int yDivNum, const Vector2& offset, float scale = 1.0f, float alpha = 1.0f);*/

private:
	//�R���X�g���N�^�A�f�X�g���N�^�̉B��
	Renderer();
	~Renderer();

	// �X�P���g���f�[�^
	std::unordered_map<std::string, class Skeleton*> mSkeletons;
	// �A�j���[�V�����f�[�^
	std::unordered_map<std::string, class Animation*> mAnims;    
	// �X�P���g�����b�V���̕`��Ɏg����
	std::vector<class SkeletalMeshComponent*>       mSkeletalMeshes;   

	//�����̃C���X�^���X
	static Renderer* mRenderer;
	SDL_Renderer* mSdlRenderer;

	/*
	@brief  �V�F�[�_�[�̓ǂݍ���
	@return true : ���� , false : ���s
	*/
	bool LoadShaders();
	/*
	@brief  Sprite�p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
	*/
	void CreateSpriteVerts();
	void CreateParticleVerts();

	void DrawParticle();

	void Draw3DScene(unsigned int _framebuffer, const Matrix4& _view, const Matrix4& _proj,
		float _viewPortScale = 1.0f, bool _lit = true);

	/*
	@brief  ���������V�F�[�_�[�̕ϐ��ɃZ�b�g����
	@param  _shader �Z�b�g����Shader�N���X�̃|�C���^
	*/
	void SetLightUniforms(Shader* _shader, const Matrix4& _view);

	void ChangeBlendMode(ParticleComponent::ParticleBlendType _blendType);
	void ChangeTexture(int _changeTextureID);

	Vector3 CalcCameraPos();

	//�t�@�C�����Ń��b�V�����擾���邽�߂̘A�z�z��
	std::unordered_map<std::string, Mesh*> mMeshes;
	//���b�V���R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
	std::vector<MeshComponent*> mMeshComponents;
	//�C���r�W�u�����b�V���R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
	std::vector<InvisibleMeshComponent*> mInvisibleMeshComponents;
	//�X�v���C�g�R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
	std::vector<SpriteComponent*> mSprites;
	//�p�[�e�B�N���̃|�C���^
	std::vector<ParticleComponent*> mParticles;
	//�t�@�C�����Ńe�N�X�`�����擾���邽�߂̘A�z�z��
	std::unordered_map<std::string, Texture*>mTextures;

	//�N���X�̃|�C���^
	//�X�v���C�g
	Shader* mSpriteShader;
	VertexArray* mSpriteVerts;
	//UI
	Shader* mUiShader;
	VertexArray* mUiVerts;
	//���b�V��
	Shader* mMeshShader;
	//�X�L�����b�V��
	Shader*  mSkinnedShader;  
	//�C���r�W�u�����b�V��
	Shader* mInvisibleMeshShader;
	Shader* mBasicShader;
	//�p�[�e�B�N��
	Shader* mParticleShader;

	// �X�J�C�{�b�N�X
	Shader* mSkyBoxShader;
	// �p�[�e�B�N���p���_��`
	VertexArray* mParticleVertex;
	// �v���C���[
	PlayerObject* mPlayer;

	// HDR �����_���[
	HDRRenderer* mHDRRenderer;
	// �L���[�u�}�b�v
	CubeMapComponent* mActiveSkyBox; // �L����(�`�悷��)�X�J�C�{�b�N�X
	// �L���[�u���_�z��
	VertexArray* mCubeVerts;


	//�r���[�s��
	Matrix4 mView;
	//�ˉe�s��
	Matrix4 mProjection;
	//�r���{�[�h�s��
	Matrix4 mBillboardMat;
	//�X�N���[���̉���
	float mScreenWidth;
	//�X�N���[���̏c��
	float mScreenHeight;
	//����
	Vector3 mAmbientLight;
	//���s����
	DirectionalLight mDirLight;
	//�E�B���h�E
	SDL_Window* mWindow;
	//�R���e�L�X�g
	SDL_GLContext mContext;
	// UI�̏������W�ɉ��Z�������W
	Vector2 mAddPosition;

	// ���ݒ�e�N�X�`���̏ꍇ�Ɋ��蓖�Ă��鍕�F�e�N�X�`��
	unsigned int mUndefineTexID;
};