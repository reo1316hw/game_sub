#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>	
/// <param name="_bossPtr"> �{�X�̃|�C���^ </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
FrontLaserMagicEffect::FrontLaserMagicEffect(BossObject* _bossPtr, const Vector3& _Scale, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MHeightCorrection(Vector3(0.0f, 0.0f, 50.0f))
	, mNowState(_bossPtr->GetNowState())
	, mBossPtr(_bossPtr)
	, mEffectComponentPtr(nullptr)
{
	// �G�t�F�N�g����
	mEffectComponentPtr = new EffectComponent(this, _Scale, u"Assets/Effect/FrontLaserMagic.efk", true, true);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void FrontLaserMagicEffect::UpdateGameObject(float _deltaTime)
{
	mPosition = mBossPtr->GetPosition() + MHeightCorrection;
	SetPosition(mPosition);
	SetRotation(mBossPtr->GetRotation());

	// �O�̃X�e�[�g
	BossState preState = mNowState;
	
	mNowState = mBossPtr->GetNowState();
	
	if (mNowState == preState)
	{
		return;
	}

	if (mNowState != BossState::eBossStateFrontAttack)
	{
		return;
	}

	// �Đ��ς݂���Ȃ�������G�t�F�N�g���Đ�����
	if (mEffectComponentPtr->IsPlayedEffect())
	{
		// �G�t�F�N�g���Đ�
		mEffectComponentPtr->PlayEffect();
	}
}