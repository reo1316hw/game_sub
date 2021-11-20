#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`�����I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_gameObjectPtr"> �v���C���[�̊��N���X�̃|�C���^ </param>
HitPointGaugeController::HitPointGaugeController(GameObject* _owner, GameObject* _gameObjectPtr)
	: Component(_owner)
	, mNowHp(0)
	, mMaxHp(static_cast<float>(_gameObjectPtr->GetHitPoint()))
	, mInitScale(mOwner->GetScale())
	, mGameObjectPtr(_gameObjectPtr)
{
}

/// <summary>
/// �t���[�����̏���
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void HitPointGaugeController::Update(float _deltaTime)
{
	// 1�t���[���O��hp
	int preHp = mNowHp;
	// ���݂�hp
	mNowHp = mGameObjectPtr->GetHitPoint();

	// 1�t���[���O��hp�ƌ��݂�hp���������e�N�X�`���̉�����ύX
	if (preHp != mNowHp)
	{
		// �k����
		float scaleDownRate = mNowHp / mMaxHp;
		// �A�^�b�`�����I�u�W�F�N�g�̑傫��
 		Vector3 scale = Vector3(mInitScale.x * scaleDownRate, mInitScale.y, mInitScale.z);
		mOwner->SetScale(scale);
	}
}