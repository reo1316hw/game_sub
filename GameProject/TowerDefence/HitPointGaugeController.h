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
	/// <param name="_gameObjectPtr"> ���N���X�̃|�C���^ </param>
	HitPointGaugeController(GameObject* _owner, GameObject* _gameObjectPtr);
	
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

	// ���݂̗̑�
	int mNowHp;

	// �ő�̗�
	float mMaxHp;

	// �A�^�b�`�����I�u�W�F�N�g�̏����̑傫��
	Vector3 mInitScale;

	// ���N���X�̃|�C���^
	GameObject* mGameObjectPtr;
};