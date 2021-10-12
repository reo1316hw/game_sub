#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_State"> �G�l�~�[�̏�� </param>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
EnemyObjectStateMove::EnemyObjectStateMove(const EnemyState& _State, PlayerObject* _playerPtr)
	: MTransitionTimingNum(120)
	, MTransitionStateDistance(15000.0f)
	, mIsMoving(false)
	, mIsDamage(false)
	, mIsHitEnemy(false)
	, mMoveSpeed(1.0f)
	, mPeriodMoveCount(0)
	, mEnemyState(_State)
	, mPlayerPtr(_playerPtr)
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
/// <returns> �G�l�~�[�̏�� </returns>
EnemyState EnemyObjectStateMove::Update(EnemyObject* _owner, const float _DeltaTime)
{
	// ���W
	Vector3 position = _owner->GetPosition();
	// �E���x�N�g��
	Vector3 rightVec = _owner->GetRight();
	rightVec.z = 0.0f;

	// �v���C���[�̍��W
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// �v���C���[�Ɍ������x�N�g��
	Vector3 dirPlayerVec = playerPos - position;

	if (mEnemyState == EnemyState::eEnemyStateLeftMove)
	{
		rightVec *= -1.0f;
	}

	// ���x�x�N�g��
	Vector3 vel = mMoveSpeed * rightVec;
	position += vel;
	_owner->SetPosition(position);
    
	++mPeriodMoveCount;

	if (mPeriodMoveCount >= MTransitionTimingNum)
	{
		if (dirPlayerVec.LengthSq() <= MTransitionStateDistance)
		{
			// �����_���l
		    int randNum = rand() % 100;
		    
		    if (randNum < 50)
		    {
		    	return EnemyState::eEnemyStateWait;
		    }
		    else
		    {
		    	return EnemyState::eEnemyStateAttack;
		    }
		}

		return EnemyState::eEnemyStateTrack;
	}
	else
	{
		if (mIsDamage)
		{
			return EnemyState::eEnemyStateDamage;
		}

		if (mIsHitEnemy)
		{
			// �����_���l
			int randNum = rand() % 100;

			if (randNum < 50)
			{
				return EnemyState::eEnemyStateWait;
			}
			else
			{
				if (mEnemyState == EnemyState::eEnemyStateLeftMove)
				{
					return EnemyState::eEnemyStateRightMove;
				}
				else
				{
					return EnemyState::eEnemyStateLeftMove;
				}
			}
		}
	}

	dirPlayerVec.Normalize();
	_owner->RotateToNewForward(dirPlayerVec);

	return mEnemyState;
}

/// <summary>
/// �G�l�~�[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void EnemyObjectStateMove::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(mEnemyState));

	mIsDamage = false;
	mIsHitEnemy = false;
	mPeriodMoveCount = 0;
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void EnemyObjectStateMove::OnColision(EnemyObject* _owner, const GameObject& _HitObject)
{
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eWeapon)
	{
		mIsDamage = true;
	}

	if (tag == Tag::eStopLateralMoveEnemy)
	{
		mIsHitEnemy = true;
	}
}