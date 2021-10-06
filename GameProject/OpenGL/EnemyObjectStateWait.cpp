#include "pch.h"

EnemyObjectStateWait::EnemyObjectStateWait(PlayerObject* _playerPtr)
	: MDistanceStop(20000.0f)
	, MTransitionTimingNum(120)
	, mIsDamage(false)
	, mPlayerPtr(_playerPtr)
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
	else if (mIsDamage)
	{
		return EnemyState::eEnemyStateDamage;
	}

	dirPlayerVec.Normalize();
	_owner->RotateToNewForward(dirPlayerVec);

	return EnemyState::eEnemyStateWait;
}

void EnemyObjectStateWait::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateWait));

	mIsDamage = false;
	mTransitionCount = 0;
}

void EnemyObjectStateWait::OnColision(const GameObject& _HitObject)
{
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::Weapon)
	{
		mIsDamage = true;
	}
}