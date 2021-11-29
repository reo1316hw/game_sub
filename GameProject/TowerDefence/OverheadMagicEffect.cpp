#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>	
/// <param name="_bossPtr"> �{�X�̃|�C���^ </param>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
OverheadMagicEffect::OverheadMagicEffect(BossObject* _bossPtr, PlayerObject* _playerPtr, const Vector3& _Scale, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MEffectPositionUnUpdateTiming(1.8f)
	, MBoxEnableTiming(2.0f)
	, mIsCollisionState(false)
	, mIsOneCollisionState(false)
	, mIsPlayEffect(false)
	, mElapseTime(0.0f)
	, MBoxDisableTiming(2.5f)
	, mBossPtr(_bossPtr)
	, mPlayerPtr(_playerPtr)
	, mEffectComponentPtr(nullptr)
{
	// �G�t�F�N�g�̋�`�����蔻��
	mBox = AABB(Vector3(-38.0f, -38.0f, 0.0f), Vector3(38.0f, 38.0f, 85.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
	// �ŏ��͓����蔻����s��Ȃ��悤�ɂ���
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	// �G�t�F�N�g����
	mEffectComponentPtr = new EffectComponent(this, _Scale, u"Assets/Effect/OverheadMagic.efk", true, true);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void OverheadMagicEffect::UpdateGameObject(float _deltaTime)
{
	// ���݂̃X�e�[�g
	BossState nowState = mBossPtr->GetNowState();

	if (nowState != BossState::eBossStateOverheadAttack)
	{
		mEffectComponentPtr->StopEffect();
		mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);
		mIsCollisionState = false;
		mIsOneCollisionState = false;
		mIsPlayEffect = false;
		mElapseTime = 0.0f;
		return;
	}

	mElapseTime += _deltaTime;

	if (mElapseTime < MEffectPositionUnUpdateTiming)
	{
		mPosition = mPlayerPtr->GetPosition();
		SetPosition(mPosition);
		return;
	}

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

	if (mElapseTime >= MBoxEnableTiming)
	{
		mBoxColliderPtr->SetCollisionState(CollisionState::eEnableCollision);
		// 1�i�K�ڂ̒ʏ�U���̓����蔻���L���ɂ���
		mIsCollisionState = true;
	}

	if (!mIsPlayEffect)
	{
		// �G�t�F�N�g���Đ�
		mEffectComponentPtr->PlayEffect();
	}

	mIsPlayEffect = true;
}