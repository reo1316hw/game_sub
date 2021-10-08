#include "pch.h"

EnemyObjectStateDamage::EnemyObjectStateDamage()
    : MAnimationTiming(20)
	, MDamageSpeed(100.0f)
    , mIsDamage(false)
	, mAnimateUntilCount(0)
	, mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
{
}

EnemyState EnemyObjectStateDamage::Update(EnemyObject* _owner, const float _DeltaTime)
{
	++mAnimateUntilCount;

	if (mAnimateUntilCount == MAnimationTiming)
	{
		SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
		meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateDamage));

		// アニメーション再生時間取得
		mTotalAnimTime = _owner->GetAnimPtr(EnemyState::eEnemyStateAttack)->GetDuration();
	}

	if (mAnimateUntilCount > MAnimationTiming)
	{
		// 座標
		Vector3 pos = _owner->GetPosition();
		// 前方ベクトル
		Vector3 forward = _owner->GetForward();
		// 開始速度
		float startSpeed = -MDamageSpeed * _DeltaTime;
		// 終了速度
		float endSpeed = MDamageSpeed * _DeltaTime;

		// 攻撃踏み込み移動のためのアニメーション再生時間の経過割合を計算
		mElapseTime += _DeltaTime;
		// 経過割合をもとに移動処理
		pos += Quintic::EaseIn(mElapseTime, startSpeed, endSpeed, mTotalAnimTime) * forward;

		_owner->SetPosition(pos);
	}
	
	// アニメーションが終了したら待機状態へ
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
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
	mIsDamage = false;
	mAnimateUntilCount = 0;
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