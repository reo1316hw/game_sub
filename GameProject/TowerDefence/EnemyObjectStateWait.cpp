#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
EnemyObjectStateWait::EnemyObjectStateWait(PlayerObject* _playerPtr)
	: MTransitionStateDistance(30000.0f)
	, MVecShortenVelue(0.1f)
	, MTransitionTimingNum(120)
	, MSeparationVecLength(8.0f)
	, mIsDamage(false)
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
	// �v���C���[�̍��W
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// �v���C���[�Ɍ������x�N�g��sd
	Vector3 dirPlayerVec = playerPos - mPosition;

	++mPeriodWaitCount;

	if (mPeriodWaitCount >= MTransitionTimingNum)
	{
		if (dirPlayerVec.LengthSq() < 15000.0f)
		{
			// �����_���l
			int randNum = rand() % 100;

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
		else if (dirPlayerVec.LengthSq() >= 15000.0f && dirPlayerVec.LengthSq() < MTransitionStateDistance)
		{
			// �����_���l
			int randNum = rand() % 90;

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
	else if(mIsDamage)
	{
		return EnemyState::eEnemyStateDamage;
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
	mPosition = _owner->GetPosition();

	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eWeapon)
	{
		mIsDamage = true;
	}
}