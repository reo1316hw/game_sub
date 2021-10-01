#pragma once

#include "Component.h"

class GameObject;
class Shader;
class Texture;
class Vector3;

/*
@file SpriteComponent.h
@brief �摜�f�[�^�N���X���Ǘ����A�X�N���[����ɕ`�悷��N���X
*/
class UIComponent : public Component
{
public:
	UIComponent(GameObject* _owner, int _drawOrder = 100);
	~UIComponent();

	/*
	@brief	�`�揈��
	@param _shader �g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
	virtual void Draw(Shader* _shader, const Vector3& _offset);

	int GetUIid() { return mMyUIid; }

protected:
	//�N���X�̃|�C���^
	Texture* mTexture;
	//�`�悳��鏇�ԁi���l�����Ȃ��قǑ����X�V�����j
	int mDrawOrder;
	//�e�N�X�`���̉���
	int mTextureWidth;
	//�e�N�X�`���̏c��
	int mTextureHeight;
	//�`����s����
	bool mVisible;

	//UI��ID�A�J�E���g�p
	static int mUIid;
	//����UI��ID
	int mMyUIid;

public://�Q�b�^�[�Z�b�^�[
	/*
	@fn �e�N�X�`�����Z�b�g���c���̒������v�Z����
	@param _texture �g�p����e�N�X�`���̃|�C���^
	*/
	virtual void SetTexture(Texture* _texture);

	/*
	@return �e�N�X�`���̉���
	*/
	int GetTexWidth() const { return mTextureWidth; }

	/*
	@return �e�N�X�`���̏c��
	*/
	int GetTexHeight() const { return mTextureHeight; }

	/*
	@return �`�揇
	*/
	int GetDrawOrder() { return mDrawOrder; }

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
private:
};

