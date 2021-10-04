#include "pch.h"

EnemyObjectStateWait::EnemyObjectStateWait(PlayerObject* _playerPtr)
	: MDistanceStop(20000.0f)
	, mPlayerPtr(_playerPtr)
	, MTransitionTimingNum(120)
	, mTransitionCount(0)
{
}

EnemyState EnemyObjectStateWait::Update(EnemyObject* _owner, const float _DeltaTime)
{
	// 座標
	Vector3 position = _owner->GetPosition();
	// プレイヤーの座標
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// プレイヤーに向いたベクトル
	Vector3 dirPlayerVec = playerPos - position;

	++mTransitionCount;

	if (mTransitionCount >= MTransitionTimingNum)
	{
		return EnemyState::eEnemyStateAttack;
	}
	else if (dirPlayerVec.LengthSq() >= MDistanceStop)
	{
		return EnemyState::eEnemyStateTrack;
	}

	return EnemyState::eEnemyStateWait;
}

void EnemyObjectStateWait::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateWait));

	mTransitionCount = 0;
}
