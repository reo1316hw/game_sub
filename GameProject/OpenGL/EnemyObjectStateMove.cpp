#include "pch.h"

EnemyObjectStateMove::EnemyObjectStateMove(PlayerObject* _playerPtr)
	: MTransitionTimingNum(120)
	, mIsMoving(false)
	, mMoveSpeed(0.5f)
	, mPeriodMoveCount(0)
{
}

EnemyState EnemyObjectStateMove::Update(EnemyObject* _owner, const float _DeltaTime)
{
	// ���W
	Vector3 pos = _owner->GetPosition();
	// �E���x�N�g��
	Vector3 rightVec = _owner->GetRight();
	rightVec.z = 0.0f;

	// �����_���l
	int randNum = rand() % 100;

	if (!mIsMoving)
	{
		// �t�����̃x�N�g���ɕϊ�
		if (randNum < 50)
		{
			mIsMoving = true;
			rightVec *= 1.0f;
		}
		else
		{
			mIsMoving = true;
			rightVec *= -1.0f;
		}
	}
	else
	{
		++mPeriodMoveCount;
	}
	
	pos += mMoveSpeed * rightVec;
	_owner->SetPosition(pos);

	if (mPeriodMoveCount >= MTransitionTimingNum)
	{
		return EnemyState::eEnemyStateWait;
	}

	return EnemyState::eEnemyStateMove;
}

void EnemyObjectStateMove::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateMove));
}