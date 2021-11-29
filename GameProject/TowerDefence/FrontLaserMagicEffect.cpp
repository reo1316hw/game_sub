#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>	
/// <param name="_bossPtr"> �{�X�̃|�C���^ </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
FrontLaserMagicEffect::FrontLaserMagicEffect(BossObject* _bossPtr, const Vector3& _Scale, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MBoxEnableTiming(0.5f)
	, MHeightCorrection(Vector3(0.0f, 0.0f, 50.0f))
	, mIsPlayEffect(false)
	, mElapseTime(0.0f)
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
	// ���݂̃X�e�[�g
	BossState nowState = mBossPtr->GetNowState();

	if (nowState != BossState::eBossStateFrontAttack)
	{
		mEffectComponentPtr->StopEffect();
		mElapseTime = 0.0f;
		mIsPlayEffect = false;
		return;
	}

	mElapseTime += _deltaTime;

	if (mElapseTime >= MBoxEnableTiming)
	{
		mPosition = mBossPtr->GetPosition() + MHeightCorrection;
		SetPosition(mPosition);
		SetRotation(mBossPtr->GetRotation());

		if (!mIsPlayEffect)
		{
			// �G�t�F�N�g���Đ�
			mEffectComponentPtr->PlayEffect();
		}

		mIsPlayEffect = true;
	}
}