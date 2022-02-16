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
	/// <param name="_Alpha"> �����x </param>
	/// <param name="_DrawOrder"> �`��̏��� </param>
	SpriteComponent(GameObject* _owner, Texture* _texture, const float _Alpha = 1.0f, const int& _DrawOrder = 100);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
    ~SpriteComponent();

    /// <summary>
    /// �`�揈��
    /// </summary>
    /// <param name="_shader"> �g�p����V�F�[�_�[�N���X�̃|�C���^ </param>
    virtual void Draw(Shader* _shader);
	
	/// <summary>
	/// �����x���グ��
	/// </summary>
	/// <param name="_PlusAlpha"> �����x�𑫂��Ă������߂̒l </param>
	/// <returns> �����x </returns>
	float IncreaseAlpha(const float _PlusAlpha);

	/// <summary>
	/// �����x�����Z�b�g
	/// </summary>
	void ResetAlpha();

private:

	// ���������x
	const float MInitAlpha;

	// �`����s����
	bool mVisible;

	// �`�悳��鏇�ԁi���l�����Ȃ��قǑ����X�V�����j
    int mDrawOrder;
	// �e�N�X�`���̉���
	int mTextureWidth;
	// �e�N�X�`���̏c��
	int mTextureHeight;
	
	// �����x
	float mAlpha;

	// �e�N�X�`���N���X�̃|�C���^
	Texture* mTexture;

public:// �Q�b�^�[�Z�b�^�[

	/// <summary>
	/// �e�N�X�`����ݒ肵�A�c���̒������v�Z����
	/// </summary>
	/// <param name="_texture"> �e�N�X�`���N���X�̃|�C���^ </param>
	void SetTexture(Texture* _texture);

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

