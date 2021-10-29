#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
EnemyObjectStateWait::EnemyObjectStateWait(PlayerObject* _playerPtr)
	: MTransitionTimingNum(120)
	, MStateTransitionProbability(100)
	, MDamageValuePlayerFirstAttack(25)
	, MTransitionStateShortDistance(15000.0f)
	, MTransitionStateMediumDistance(30000.0f)
	, MVecShortenVelue(0.1f)
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
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
/// <returns> �G�l�~�[�̏�� </returns>
EnemyState EnemyObjectStateWait::Update(EnemyObject* _owner, const float _DeltaTime)
{
	// ���W
	mPosition = _owner->GetPosition();
	// �v���C���[�̍��W
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// �v���C���[�Ɍ������x�N�g��sd
	Vector3 dirPlayerVec = playerPos - mPosition;

	++mPeriodWaitCount;

	if (mIsDamage)
	{
		return EnemyState::eEnemyStateDamage;
	}

	if (mPeriodWaitCount >= MTransitionTimingNum)
	{
		// �����_���l
		int randNum = rand() % MStateTransitionProbability;

		if (dirPlayerVec.LengthSq() < MTransitionStateShortDistance)
		{
			if (randNum < 25)
			{
				return EnemyState::eEnemyStateWait;
			}
			else if(randNum >= 25 && randNum < 50)
			{
				return EnemyState::eEnemyStateLeftMove;
			}
			else if (randNum >= 50 && randNum < 75)
			{
				return EnemyState::eEnemyStateRightMove;
			}
			else
			{
				return EnemyState::eEnemyStateAttackReady;
			}
		}
		else if (dirPlayerVec.LengthSq() >= MTransitionStateShortDistance &&
			     dirPlayerVec.LengthSq() < MTransitionStateMediumDistance)
		{
			if (randNum < 30)
			{
				return EnemyState::eEnemyStateWait;
			}
			else if (randNum >= 30 && randNum < 60)
			{
				return EnemyState::eEnemyStateLeftMove;
			}
			else
			{
				return EnemyState::eEnemyStateRightMove;
			}
		}

		return EnemyState::eEnemyStateTrack;
	}

	dirPlayerVec.Normalize();
	_owner->RotateToNewForward(dirPlayerVec);

	return EnemyState::eEnemyStateWait;
}

/// <summary>
/// �G�l�~�[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void EnemyObjectStateWait::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateWait));

	mIsDamage = false;
	mPeriodWaitCount = 0;
}

/// <summary>
/// �G�l�~�[���m�̈�������
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DirTargetEnemyVec"> �ΏۂƂȂ�G�l�~�[�Ɍ������x�N�g�� </param>
void EnemyObjectStateWait::Separation(EnemyObject* _owner, const Vector3& _DirTargetEnemyVec)
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
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void EnemyObjectStateWait::OnCollision(EnemyObject* _owner, const GameObject& _HitObject)
{
	// �I�u�W�F�N�g�̃^�O
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eDashAttackEffect)
	{
		mDamageValue = MDamageValuePlayerFirstAttack;
		mIsDamage = true;
		return;
	}

	if (tag == Tag::eFirstAttackEffect)
	{
		mDamageValue = MDamageValuePlayerFirstAttack;
		mIsDamage = true;
		return;
	}

	if (tag == Tag::eSecondAttackEffect)
	{
		mDamageValue = MDamageValuePlayerFirstAttack;
		mIsDamage = true;
		return;
	}

	if (tag == Tag::eThirdAttackEffect)
	{
		mDamageValue = MDamageValuePlayerFirstAttack;
		mIsDamage = true;
		return;
	}

	_owner->SetDamageValue(mDamageValue);
}