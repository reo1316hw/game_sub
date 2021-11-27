#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>	
/// <param name="_bossPtr"> �{�X�̃|�C���^ </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
AreaMagicEffect::AreaMagicEffect(BossObject* _bossPtr, const Vector3& _Scale, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MBoxEnableTiming(2.2f)
	, MBoxDisableTiming(2.5f)
	, MHeightCorrection(Vector3(0.0f, 0.0f, 50.0f))
	, mIsCollisionState(false)
	, mIsOneCollisionState(false)
	, mElapseTime(0.0f)
	, mNowState(_bossPtr->GetNowState())
	, mBossPtr(_bossPtr)
	, mEffectComponentPtr(nullptr)
{
	// �G�t�F�N�g�̋�`�����蔻��
	mBox = AABB(Vector3(-250.0f, -250.0f, -100.0f), Vector3(250.0f, 250.0f, 100.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
	// �ŏ��͓����蔻����s��Ȃ��悤�ɂ���
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	// �G�t�F�N�g����
	mEffectComponentPtr = new EffectComponent(this, _Scale, u"Assets/Effect/AreaMagic.efk", true, true);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void AreaMagicEffect::UpdateGameObject(float _deltaTime)
{
	// �O�̃X�e�[�g
	BossState preState = mNowState;

	mNowState = mBossPtr->GetNowState();

	if (mNowState != BossState::eBossStateAreaAttack)
	{
		mEffectComponentPtr->StopEffect();
		mIsOneCollisionState = false;
		mElapseTime = 0.0f;
		return;
	}

	mElapseTime += _deltaTime;

	if (mIsCollisionState)
	{
		if (mElapseTime >= MBoxDisableTiming)
		{
			mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

			// 1�i�K�ڂ̒ʏ�U���̓����蔻��𖳌��ɂ���
			mIsCollisionState = false;
			mIsOneCollisionState = true;
		}
	}

	if (mIsOneCollisionState)
	{
		return;
	}

	mPosition = mBossPtr->GetPosition() + MHeightCorrection;
	SetPosition(mPosition);
	SetRotation(mBossPtr->GetRotation());

	if (mElapseTime >= MBoxEnableTiming)
	{
		mBoxColliderPtr->SetCollisionState(CollisionState::eEnableCollision);
		// 1�i�K�ڂ̒ʏ�U���̓����蔻���L���ɂ���
		mIsCollisionState = true;
	}

	if (mNowState == preState)
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