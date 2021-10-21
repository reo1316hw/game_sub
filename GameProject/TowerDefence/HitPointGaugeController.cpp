#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`�����I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_texture"> �e�N�X�`����� </param>
HitPointGaugeController::HitPointGaugeController(GameObject* _owner, Texture* _texture)
	: Component(_owner)
	, mTextureWidthAfterChange(0)
	, mTextureMaxWidth(_texture->GetWidth())
	, mNowHp(0)
	, mMaxHp(static_cast<float>(mOwner->GetHitPoint()))
{
}

/// <summary>
/// �ύX��̃e�N�X�`���̉������擾����
/// </summary>
/// <returns> �ύX��̃e�N�X�`���̉��� </returns>
void HitPointGaugeController::Update(float _deltaTime)
{
	// 1�t���[���O��hp
	int preHp = mNowHp;
	// ���݂�hp
	mNowHp = mOwner->GetHitPoint();

	// 1�t���[���O��hp�ƌ��݂�hp���������e�N�X�`���̉�����ύX
	if (preHp != mNowHp)
	{
		// �k����
		float scaleDownRate = mNowHp / mMaxHp;
		mTextureWidthAfterChange = scaleDownRate * mTextureMaxWidth;
	}
}