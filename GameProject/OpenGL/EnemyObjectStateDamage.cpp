#include "pch.h"

EnemyObjectStateDamage::EnemyObjectStateDamage()
    : mIsDamage(false)
	, mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
{
}

EnemyState EnemyObjectStateDamage::Update(EnemyObject* _owner, const float _DeltaTime)
{
	mElapseTime += _DeltaTime;

	// アニメーションが終了したら待機状態へ
	if (mElapseTime >= 0.3f)
	{
		return EnemyState::eEnemyStateWait;
	}
	else if (mIsDamage)
	{
		return EnemyState::eEnemyStateDamage;
	}

	return EnemyState::eEnemyStateDamage;
}

void EnemyObjectStateDamage::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateDamage));

	mIsDamage = false;
	// アニメーション再生時間取得
	mTotalAnimTime = _owner->GetAnimPtr(EnemyState::eEnemyStateDamage)->GetDuration();
	mElapseTime = 0.0f;
}

void EnemyObjectStateDamage::OnColision(const GameObject& _HitObject)
{
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::Weapon)
	{
		mIsDamage = true;
	}
}