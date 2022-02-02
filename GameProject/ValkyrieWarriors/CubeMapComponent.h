#pragma once

/// <summary>
/// �L���[�u�}�b�v�̊Ǘ��ƕ`����s��
/// </summary>
class CubeMapComponent : public Component
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner"> �e�N���X�̃|�C���^ </param>
	CubeMapComponent(GameObject* _owner);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CubeMapComponent();

	/// <summary>
	/// texture��������
	/// </summary>
	/// <param name="_TextureName"> �g�p����texture�̃t�@�C���p�X </param>
	void CreateTexture(const std::string& _TextureName);

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="_shader"> �g�p����V�F�[�_�[�N���X�̃|�C���^ </param>
	void Draw(Shader* _shader);

private:

	// �`�悷�邩�̃t���O
	bool mIsVisible;

	// �P�x���
	float mLuminance;

	// �e�N�X�`���̃|�C���^
	Texture* mTexture;

public:// �Q�b�^�[�Z�b�^�[

	/// <summary>
	/// �X�J�C�{�b�N�X�Ɏg�p���Ă���e�N�X�`���̃|�C���^���擾
	/// </summary>
	/// <returns> �X�J�C�{�b�N�X�Ɏg�p���Ă���e�N�X�`���̃|�C���^ </returns>
	Texture* GetSkyBoxTexture() { return mTexture; }

	/// <summary>
	/// �L���[�u��\�����邩�̃t���O��ݒ�
	/// </summary>
	/// <param name="_isVisible"> �L���[�u��\�����邩�̃t���O </param>
	void SetIsVisible(bool _isVisible) { mIsVisible = _isVisible; }

	/// <summary>
	/// �P�x����ݒ�
	/// </summary>
	/// <param name="_luminance"> �P�x��� </param>
	void SetLuminance(float _luminance) { mLuminance = _luminance; }
};

