#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
BossObjectStateOverheadAttack::BossObjectStateOverheadAttack(PlayerObject* _playerPtr)
	: mHitTagList{ Tag::eDashAttackEffect, Tag::eFirstAttackEffect, Tag::eSecondAttackEffect, Tag::eThirdAttackEffect }
	, mDamageValueList{ 10, 5, 15, 25 }
	, MTransitionStateDistance(30000.0f)
	, MVecShortenVelue(0.1f)
	, MSeparationVecLength(8.0f)
	, mIsDamage(false)
	, mDashAttackIsChangeHitPoint(false)
	, mFirstAttackIsChangeHitPoint(false)
	, mDamageValue(0)
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
BossState BossObjectStateOverheadAttack::Update(BossObject* _owner, const float _DeltaTime)
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

	_owner->SetPosition(mPosition);

	// �v���C���[�̍��W
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// �v���C���[�Ɍ������x�N�g��sd
	Vector3 dirPlayerVec = playerPos - mPosition;

	// �A�j���[�V�������I��������ړ���Ԃ�
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		if (dirPlayerVec.LengthSq() < MTransitionStateDistance)
		{
			// �����_���l
			int randNum = rand() % 100;

			if (randNum < 50)
			{
				return BossState::eBossStateWait;
			}
			else
			{
				return BossState::eBossStateTeleportation;
			}
		}

		return BossState::eBossStateTrack;
	}

	return BossState::eBossStateOverheadAttack;
}

/// <summary>
/// �{�X�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void BossObjectStateOverheadAttack::Enter(BossObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(BossState::eBossStateOverheadAttack));

	mIsDamage = false;

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
void BossObjectStateOverheadAttack::Separation(BossObject* _owner, const Vector3& _DirTargetEnemyVec)
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
void BossObjectStateOverheadAttack::OnCollision(BossObject* _owner, const GameObject& _HitObject)
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
bool BossObjectStateOverheadAttack::ReceivedAttack(const Tag& _hitTag, const int& _DamageValuePlayerAttack)
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
void BossObjectStateOverheadAttack::SufferDamage(BossObject* _owner)
{
	// �_���[�W�l
	int damageValue = _owner->GetDamageValue();
	// �̗�
	mHitPoint = _owner->GetHitPoint() - damageValue;

	// �I�u�W�F�N�g�̃X�P�[���T�C�Y�����߂邽�߂̍��ӂ̒l��ݒ�
	_owner->SetScaleLeftSideValue(mHitPoint);
	_owner->SetHitPoint(mHitPoint);
}