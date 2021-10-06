#include "pch.h"

EnemyObjectStateMove::EnemyObjectStateMove(PlayerObject* _playerPtr)
	: MTransitionTimingNum(120)
	, mIsMoving(false)
	, mMoveSpeed(1.0f)
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
		}
		else
		{
			mIsMoving = true;
			mMoveSpeed *= -1.0f;
		}
	}
	else
	{
		++mPeriodMoveCount;
	}
	
	Vector3 vel = mMoveSpeed * rightVec;
	pos += vel;
	_owner->SetPosition(pos);

	if (mPeriodMoveCount >= MTransitionTimingNum)
	{
		mIsMoving = false;
		return EnemyState::eEnemyStateWait;
	}

	return EnemyState::eEnemyStateMove;
}

void EnemyObjectStateMove::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateMove));

	mPeriodMoveCount = 0;
}