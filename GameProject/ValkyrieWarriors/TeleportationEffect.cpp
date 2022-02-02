#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>	
/// <param name="_bossPtr"> �{�X�̃|�C���^ </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
TeleportationEffect::TeleportationEffect(BossObject* _bossPtr, const Vector3& _Scale, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MPlayRate(5.0f)
	, MHeightCorrection(Vector3(0.0f, 0.0f, 50.0f))
	, mIsPlayEffect(false)
	, mNowState(_bossPtr->GetNowState())
	, mBossPtr(_bossPtr)
	, mEffectComponentPtr(nullptr)
{
	// �G�t�F�N�g����
	mEffectComponentPtr = new EffectComponent(this, _Scale, u"Assets/Effect/Telepotation.efk", true, true);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void TeleportationEffect::UpdateGameObject(float _deltaTime)
{
	// �O�̃X�e�[�g
	BossState preState = mNowState;

	mNowState = mBossPtr->GetNowState();

	if (mNowState == preState)
	{
		mIsPlayEffect = false;
		return;
	}

	if (preState == BossState::eBossStateTeleportation)
	{
		mPosition = mBossPtr->GetPosition() + MHeightCorrection;
		SetPosition(mPosition);
		SetRotation(mBossPtr->GetRotation());

		// �G�t�F�N�g���Đ�
		mEffectComponentPtr->PlayEffect(MPlayRate);
		return;
	}

	if (mNowState != BossState::eBossStateTeleportation)
	{
		mIsPlayEffect = false;
		return;
	}

	mPosition = mBossPtr->GetPosition() + MHeightCorrection;
	SetPosition(mPosition);
	SetRotation(mBossPtr->GetRotation());

	if (!mIsPlayEffect)
	{
		// �G�t�F�N�g���Đ�
		mEffectComponentPtr->PlayEffect(MPlayRate);
	}

	mIsPlayEffect = true;
}