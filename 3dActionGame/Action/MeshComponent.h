#pragma once

#include "Component.h"

class GameObject;
class Shader;
class Mesh;

/*
 @file MeshComponent.h
 @brief ���b�V���f�[�^�̊Ǘ��ƕ`����s��
*/
class MeshComponent : public Component
{
public:
	/*
	@param _skelton �X�P���g���f�[�^��p���邩�B
	@sa SkeletalMeshComponent.h
	*/
    MeshComponent(GameObject* _owner,bool _skelton=false);
    ~MeshComponent();

	/*
	@brief�@�`�揈��
	@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
    virtual void Draw(Shader* _shader);
protected:

	virtual void SetTextureToShader(class Shader* shader);

	//���b�V���f�[�^�N���X�ւ̃|�C���^
    Mesh* mMesh;
	//�e�N�X�`���T�C�Y
    size_t mTextureIndex;
	//�`������邩�ǂ���
	bool mVisible;
	//�X�P���g���f�[�^��p���邩
	bool mSkeltonFlag;
public: //�Q�b�^�[�Z�b�^�[
	/*
	@brief�@���b�V���R���|�[�l���g���g��Mesh�̐ݒ�
	@param	_mesh �ݒ肷��Mesh�N���X�̃|�C���^
	*/
	virtual void SetMesh(Mesh* _mesh) { mMesh = _mesh; }

	/*
	 �@@return �ݒ肳�ꂽMesh�N���X�̃|�C���^
	*/
	virtual Mesh* GetMesh() { return mMesh; }

	/*
	@brief�@���b�V���R���|�[�l���g���g��Texture�C���f�b�N�X�̐ݒ�
	*/
	void SetTextureIndex(size_t _index) { mTextureIndex = _index; }

	/*
	@brief�@�`������邩�ǂ�����ݒ�
	@param	true : �`�悷�� , false : �`�悵�Ȃ�
	*/
	void SetVisible(bool _visible) { mVisible = _visible; }

	/*
	@brief�@�`������邩�ǂ������擾����
	@return	true : �`�悷�� , false : �`�悵�Ȃ�
	*/
	bool GetVisible() const { return mVisible; }

	/*
	@return �X�P���g���f�[�^��p���邩
	*/
	bool GetIsSkeltal()const { return mSkeltonFlag; }
};

