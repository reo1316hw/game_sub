#pragma once

// �O���錾
class GameObject;
class Shader;
class Texture;

/*
@file SpriteComponent.h
@brief �摜�f�[�^�N���X���Ǘ����A�X�N���[����ɕ`�悷��N���X
*/
class SpriteComponent : public Component
{
public:

	SpriteComponent(GameObject* _owner, Texture* _texture, int _drawOrder = 100);
    SpriteComponent(GameObject* _owner, Texture* _texture, HitPointGaugeController* _hitPointGaugeController, int _drawOrder = 100);
    ~SpriteComponent();

	/*
	@brief	�`�揈��
	@param _shader �g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
    virtual void Draw(Shader* _shader);
protected:
	
	// �`����s����
	bool mVisible;

	// �`�悳��鏇�ԁi���l�����Ȃ��قǑ����X�V�����j
    int mDrawOrder;
	// �e�N�X�`���̉���
    int mTextureWidth;
	// �e�N�X�`���̏c��
    int mTextureHeight;

	// hp�Q�[�W�𐧌䂷��R���|�[�l���g�N���X�̃|�C���^
	HitPointGaugeController* mHitPointGaugeControllerPtr;
	// �N���X�̃|�C���^
	Texture* mTexture;

public://�Q�b�^�[�Z�b�^�[

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
};

