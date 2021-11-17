#pragma once

// �O���錾
class GameObject;
class Shader;
class Texture;

/// <summary>
/// �摜�f�[�^�N���X���Ǘ����A�X�N���[����ɕ`�悷��N���X
/// </summary>
class SpriteComponent : public Component
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_texture"> �e�N�X�`���̃|�C���^ </param>
	/// <param name="_Scale"> �e�N�X�`���̊g��T�C�Y </param>
	/// <param name="_DrawOrder"> �`��̏��� </param>
	SpriteComponent(GameObject* _owner, Texture* _texture, const Vector2& _Scale , const int& _DrawOrder = 100);

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_texture"> �e�N�X�`���̃|�C���^ </param>
	/// <param name="_hitPointGaugeController"> hp�Q�[�W�𐧌䂷��N���X�̃|�C���^ </param>
	/// <param name="_Scale"> �e�N�X�`���̊g��T�C�Y </param>
	/// <param name="_DrawOrder"> �`��̏��� </param>
    SpriteComponent(GameObject* _owner, Texture* _texture, HitPointGaugeController* _hitPointGaugeController,
		const Vector2& _Scale, const int& _DrawOrder = 100);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
    ~SpriteComponent();

    /// <summary>
    /// �`�揈��
    /// </summary>
    /// <param name="_shader"> �g�p����V�F�[�_�[�N���X�̃|�C���^ </param>
    virtual void Draw(Shader* _shader);

private:
	
	// �e�N�X�`���̑傫��
	const Vector2 MScale;

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

public:// �Q�b�^�[�Z�b�^�[

	/// <summary>
	/// �`�揇���擾
	/// </summary>
	/// <returns> �`�揇 </returns>
	int GetDrawOrder() { return mDrawOrder; }

	/// <summary>
	/// �`������邩�ǂ����̃t���O���擾����
	/// </summary>
	/// <returns> true : �`�悷�� , false : �`�悵�Ȃ� </returns>
	bool GetVisible() const { return mVisible; }

	/// <summary>
	/// �`������邩�ǂ����̃t���O��ݒ�
	/// </summary>
	/// <param name="_visible"> �`������邩�ǂ����̃t���O </param>
	void SetVisible(bool _visible) { mVisible = _visible; }
};

