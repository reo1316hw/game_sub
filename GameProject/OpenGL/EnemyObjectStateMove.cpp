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
	// 座標
	Vector3 pos = _owner->GetPosition();
	// 右方ベクトル
	Vector3 rightVec = _owner->GetRight();
	rightVec.z = 0.0f;

	// ランダム値
	int randNum = rand() % 100;

	if (!mIsMoving)
	{
		// 逆向きのベクトルに変換
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