#include "pch.h"

EnemyObjectStateDeath::EnemyObjectStateDeath()
	: mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
{
}

EnemyState EnemyObjectStateDeath::Update(EnemyObject* _owner, const float _DeltaTime)
{
	mElapseTime += _DeltaTime;

	// アニメーションが終了したら更新を止める
	if (mElapseTime >= 0.3f)
	{
		_owner->SetState(Dead);
	}

	return EnemyState::eEnemyStateDeath;
}

void EnemyObjectStateDeath::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateDeath));

	// アニメーション再生時間取得
	mTotalAnimTime = _owner->GetAnimPtr(EnemyState::eEnemyStateDeath)->GetDuration();
	mElapseTime = 0.0f;
}