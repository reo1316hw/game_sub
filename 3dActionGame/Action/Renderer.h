#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "Math.h"
#include "ParticleComponent.h"
#include "PlayerObject.h"

#define RENDERER Renderer::GetInstance()

//���s�����p�̍\����
struct DirectionalLight
{
	// ���̕���
	Vector3 direction;
	// �g�U���ːF
	Vector3 diffuseColor;
	// ���ʔ��ːF
	Vector3 specColor;
};

enum class TextureStage
{
	DiffuseMap,
	NormalMap,
	SpecularMap,
	EmissiveMap,
	ShadowMap,
};

class SpriteComponent;
class Texture;
class Mesh;
class Game;
class MeshComponent;
class InvisibleMeshComponent;
class Shader;
class VertexArray;
class ParticleComponent;
class UIComponent;
class HeartUI;
class HDRRenderer;

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
	static Renderer* GetInstance() { return renderer; }

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
	@brief  UI�̒ǉ�
	@param	_ui�@�ǉ�����UI�N���X�̃|�C���^
	*/
	void AddUI(UIComponent* _ui);

	/*
	@brief UI�̍폜
	@param	_ui�@�폜����UI�N���X�̃|�C���^
	*/
	void RemoveUI(UIComponent* _ui);

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
	const class Skeleton* GetSkeleton(const char* fileName);                       
	/*
	@param _fileName �A�j���[�V�����ւ̃A�h���X
	@return �X�P���g���A�j���[�V�����̎擾
	*/
	const class Animation* GetAnimation(const char* fileName, bool _loop);                     // �X�P���^���A�j���[�V�����̎擾

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
	void SetViewMatrix(const Matrix4& _view) { view = _view; }

	/*
	@brief	������ݒ肷��
	@param	_ambient Vector3�i������\���j
	*/
	void SetAmbientLight(const Vector3& _ambient) { ambientLight = _ambient; }

	/*
	@brief	���s�����̍\���̂��擾����
	@return	DirectionalLight�i���s�����̍\���́j
	*/
	DirectionalLight& GetDirectionalLight() { return dirLight; }

	/*
	@brief	�X�N���[���̉������擾����
	@return	�X�N���[���̉���
	*/
	float GetScreenWidth() const { return screenWidth; }

	/*
	@brief	�X�N���[���̏c�����擾����
	@return	�X�N���[���̏c��
	*/
	float GetScreenHeight() const { return screenHeight; }

	Matrix4 GetViewMatrix() const { return view; };

	void SetParticleVertex();

	Matrix4 GetProjectionMatrix() { return projection; }

	SDL_Renderer* GetSDLRenderer() { return sdlRenderer; }

	unsigned int GetUndefineTexID() { return mUndefineTexID; }

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
	static Renderer* renderer;
	SDL_Renderer* sdlRenderer;

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

	void Draw3DScene(unsigned int framebuffer, const Matrix4& view, const Matrix4& proj,
		float viewPortScale = 1.0f, bool lit = true);

	/*
	@brief  ���������V�F�[�_�[�̕ϐ��ɃZ�b�g����
	@param  _shader �Z�b�g����Shader�N���X�̃|�C���^
	*/
	void SetLightUniforms(Shader* _shader, const Matrix4& view);

	void ChangeBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM blendType);
	void ChangeTexture(int changeTextureID);

	Vector3 CalcCameraPos();

	//�t�@�C�����Ń��b�V�����擾���邽�߂̘A�z�z��
	std::unordered_map<std::string, Mesh*> meshes;
	//���b�V���R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
	std::vector<MeshComponent*> meshComponents;
	//�C���r�W�u�����b�V���R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
	std::vector<InvisibleMeshComponent*> invisibleMeshComponents;
	//�X�v���C�g�R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
	std::vector<SpriteComponent*> sprites;
	//UI�̃|�C���^�̉ϒ��R���e�i
	std::vector<UIComponent*> uis;
	//�p�[�e�B�N���̃|�C���^
	std::vector<ParticleComponent*> particles;
	//�t�@�C�����Ńe�N�X�`�����擾���邽�߂̘A�z�z��
	std::unordered_map<std::string, Texture*>textures;

	//�N���X�̃|�C���^
	//�X�v���C�g
	Shader* spriteShader;
	VertexArray* spriteVerts;
	//UI
	Shader* uiShader;
	VertexArray* uiVerts;
	//���b�V��
	Shader* meshShader;
	//�X�L�����b�V��
	class Shader*  mSkinnedShader;  
	//�C���r�W�u�����b�V��
	Shader* invisibleMeshShader;
	Shader* basicShader;
	//�p�[�e�B�N��
	Shader* particleShader;
	// �p�[�e�B�N���p���_��`
	VertexArray* particleVertex;   
	// �v���C���[
	PlayerObject* player;

	// HDR �����_���[
	HDRRenderer* mHDRRenderer;

	//�r���[�s��
	Matrix4 view;
	//�ˉe�s��
	Matrix4 projection;
	//�r���{�[�h�s��
	Matrix4 mBillboardMat;
	//�X�N���[���̉���
	float screenWidth;
	//�X�N���[���̏c��
	float screenHeight;
	//����
	Vector3 ambientLight;
	//���s����
	DirectionalLight dirLight;
	//�E�B���h�E
	SDL_Window* window;
	//�R���e�L�X�g
	SDL_GLContext context;
	// UI�̏������W�ɉ��Z�������W
	Vector2 addPosition;

	HeartUI* heartUI;

	// ���ݒ�e�N�X�`���̏ꍇ�Ɋ��蓖�Ă��鍕�F�e�N�X�`��
	unsigned int mUndefineTexID;
};