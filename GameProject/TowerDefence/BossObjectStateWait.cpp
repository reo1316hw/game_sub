#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
BossObjectStateWait::BossObjectStateWait(PlayerObject* _playerPtr)
	: mHitTagList{ Tag::eDashAttackEffect, Tag::eFirstAttackEffect, Tag::eSecondAttackEffect, Tag::eThirdAttackEffect }
	, mDamageValueList{ 10, 5, 15, 25 }
	, MTransitionStateDistance(30000.0f)
	, MVecShortenVelue(0.1f)
	, MTransitionTimingNum(60)
	, MSeparationVecLength(8.0f)
	, mIsDamage(false)
	, mDashAttackIsChangeHitPoint(false)
	, mFirstAttackIsChangeHitPoint(false)
	, mDamageValue(0)
	, mPeriodWaitCount(0)
	, mHitTagListSize(sizeof(mHitTagList) / sizeof(int))
	, mHitPoint(0)
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
	, mHitTag(Tag::eOther)
	, mBossPtr(nullptr)
	, mPlayerPtr(_playerPtr)
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
/// <returns> �{�X�̏�� </returns>
BossState BossObjectStateWait::Update(BossObject* _owner, const float _DeltaTime)
{
	if (mPlayerPtr->GetNowState() != PlayerState::ePlayerStateDashAttack)
	{
		mDashAttackIsChangeHitPoint = false;
	}

	if (mPlayerPtr->GetNowState() != PlayerState::ePlayerStateFirstAttack)
	{
		mFirstAttackIsChangeHitPoint = false;
	}

	if (mIsDamage)
	{
		switch (mHitTag)
		{
		case Tag::eDashAttackEffect:

			// hp���ύX���ꂽ��_���[�W�𕉂����������݂̃X�e�[�g�Ɏ������܂ōs��Ȃ��悤�ɂ���
			if (mDashAttackIsChangeHitPoint)
			{
				break;
			}

			// �_���[�W�𕉂�����
			SufferDamage(_owner);

			mDashAttackIsChangeHitPoint = true;

			break;

		case Tag::eFirstAttackEffect:

			// hp���ύX���ꂽ��_���[�W�𕉂����������݂̃X�e�[�g�Ɏ������܂ōs��Ȃ��悤�ɂ���
			if (mFirstAttackIsChangeHitPoint)
			{
				break;
			}

			// �_���[�W�𕉂�����
			SufferDamage(_owner);

			mFirstAttackIsChangeHitPoint = true;

			break;

		case Tag::eSecondAttackEffect:

			return BossState::eBossStateSweepFallDamage;

		case Tag::eThirdAttackEffect:

			return BossState::eBossStateFlyingBackDamage;
		}
	}

	if (mHitPoint <= 0)
	{
		return BossState::eBossStateDeath;
	}

	mIsDamage = false;

	// �v���C���[�̍��W
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// �v���C���[�Ɍ������x�N�g��sd
	Vector3 dirPlayerVec = playerPos - mPosition;

	++mPeriodWaitCount;

	if (mPeriodWaitCount >= MTransitionTimingNum)
	{
		// �����_���l
		int randNum = rand() % 100;

		if (dirPlayerVec.LengthSq() < MTransitionStateDistance)
		{
			if (randNum < 25)
			{
				return BossState::eBossStateAreaAttack;
			}
			else if (randNum >= 25 && randNum < 50)
			{
				return BossState::eBossStateFrontAttack;
			}
			else if (randNum >= 50 && randNum < 75)
			{
				return BossState::eBossStateOverheadAttack;
			}
			else
			{
				return BossState::eBossStateTeleportation;
			}
		}

		if (randNum < 30)
		{
			return BossState::eBossStateFrontAttack;
		}
		else if (randNum >= 30 && randNum < 60)
		{
			return BossState::eBossStateOverheadAttack;
		}
		else
		{
			return BossState::eBossStateTeleportation;
		}
	}

	dirPlayerVec.Normalize();
	_owner->RotateToNewForward(dirPlayerVec);

	return BossState::eBossStateWait;
}

/// <summary>
/// �{�X�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void BossObjectStateWait::Enter(BossObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(BossState::eBossStateWait));

	mIsDamage = false;
	mPeriodWaitCount = 0;

	// �̗�
	mHitPoint = _owner->GetHitPoint();
	// ���W
	mPosition = _owner->GetPosition();
}

/// <summary>
/// �{�X�ƃG�l�~�[�̈�������
/// </summary>
/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
/// <param name="_DirTargetEnemyVec"> �ΏۂƂȂ�G�l�~�[�Ɍ������x�N�g�� </param>
void BossObjectStateWait::Separation(BossObject* _owner, const Vector3& _DirTargetEnemyVec)
{
	// ���W
	mPosition = _owner->GetPosition();
	// ���������x�N�g��
	Vector3 separationVec = MSeparationVecLength * _DirTargetEnemyVec;

	mVelocity -= separationVec;
	mVelocity *= MVecShortenVelue;
	mPosition += mVelocity;

	_owner->SetPosition(mPosition);
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void BossObjectStateWait::OnCollision(BossObject* _owner, const GameObject& _HitObject)
{
	mBossPtr = _owner;
	// ���W
	mPosition = mBossPtr->GetPosition();

	// �I�u�W�F�N�g�̃^�O
	mHitTag = _HitObject.GetTag();

	for (int i = 0; i < mHitTagListSize; i++)
	{
		// �U�����󂯂����̏���
		if (ReceivedAttack(mHitTagList[i], mDamageValueList[i]))
		{
			return;
		}
	}
}

/// <summary>
/// �U�����󂯂����̏���
/// </summary>
/// <param name="_HitTag"> �q�b�g�����I�u�W�F�N�g�̃^�O </param>
/// <param name="_DamageValuePlayerAttack"> �_���[�W�� </param>
/// <returns> �q�b�g������ </returns>
bool BossObjectStateWait::ReceivedAttack(const Tag& _hitTag, const int& _DamageValuePlayerAttack)
{
	if (mHitTag == _hitTag)
	{
		mDamageValue = _DamageValuePlayerAttack;
		mIsDamage = true;

		mBossPtr->SetDamageValue(mDamageValue);
		return true;
	}

	return false;
}

/// <summary>
/// �_���[�W�𕉂�����
/// </summary>
/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
void BossObjectStateWait::SufferDamage(BossObject* _owner)
{
	// �_���[�W�l
	int damageValue = _owner->GetDamageValue();
	// �̗�
	mHitPoint = _owner->GetHitPoint() - damageValue;

	// �I�u�W�F�N�g�̃X�P�[���T�C�Y�����߂邽�߂̍��ӂ̒l��ݒ�
	_owner->SetScaleLeftSideValue(mHitPoint);
	_owner->SetHitPoint(mHitPoint);
}