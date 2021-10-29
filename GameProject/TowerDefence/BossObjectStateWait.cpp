#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
BossObjectStateWait::BossObjectStateWait(PlayerObject* _playerPtr)
	: MDamageValuePlayerFirstAttack(25)
	, MTransitionStateDistance(30000.0f)
	, MVecShortenVelue(0.1f)
	, MTransitionTimingNum(120)
	, MSeparationVecLength(8.0f)
	, mIsDamage(false)
	, mDamageValue(0)
	, mPeriodWaitCount(0)
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
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
	// �v���C���[�̍��W
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// �v���C���[�Ɍ������x�N�g��sd
	Vector3 dirPlayerVec = playerPos - mPosition;

	++mPeriodWaitCount;

	if (mIsDamage)
	{
		return BossState::eBossStateDamage;
	}

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
	// �I�u�W�F�N�g�̃^�O
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eFirstAttackEffect)
	{
		mDamageValue = MDamageValuePlayerFirstAttack;
		mIsDamage = true;
	}

	if (tag == Tag::eSecondAttackEffect)
	{
		mDamageValue = MDamageValuePlayerFirstAttack;
		mIsDamage = true;
	}

	if (tag == Tag::eThirdAttackEffect)
	{
		mDamageValue = MDamageValuePlayerFirstAttack;
		mIsDamage = true;
	}

	_owner->SetDamageValue(mDamageValue);
}