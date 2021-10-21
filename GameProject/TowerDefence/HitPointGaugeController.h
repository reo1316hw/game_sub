#pragma once

/// <summary>
/// hp�Q�[�W�𐧌䂷��
/// </summary>
class HitPointGaugeController : public Component
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner"> �A�^�b�`�����I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_texture"> �e�N�X�`����� </param>
	HitPointGaugeController(GameObject* _owner, Texture* _texture);
	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~HitPointGaugeController() {};

	/// <summary>
	/// �t���[�����̏���
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void Update(float _deltaTime)override;

private:

	// �ύX��̃e�N�X�`���̉���
	int mTextureWidthAfterChange;
	// �e�N�X�`���̍ő剡��
	int mTextureMaxWidth;
	// ���݂̗̑�
	int mNowHp;

	// �ő�̗�
	float mMaxHp;

public:// �Q�b�^�[�Z�b�^�[

	/// <summary>
	/// �ύX��̃e�N�X�`���̉������擾����
	/// </summary>
	/// <returns> �ύX��̃e�N�X�`���̉��� </returns>
	int GetTextureWidthAfterChange() { return mTextureWidthAfterChange; }
};