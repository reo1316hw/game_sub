#include "pch.h"

EnemyObjectStateAttack::EnemyObjectStateAttack(PlayerObject* _playerPtr)
	: MAttackSpeed(300.0f)
	, mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
	, mPlayerPtr(_playerPtr)
{
}

EnemyState EnemyObjectStateAttack::Update(EnemyObject* _owner, const float _DeltaTime)
{
	// 攻撃踏み込み移動のためのアニメーション再生時間の経過割合を計算
	mElapseTime += _DeltaTime;

	// 経過割合をもとに移動処理
	Vector3 pos, forward;
	pos = _owner->GetPosition();
	forward = _owner->GetForward();
	float differencePos = -MAttackSpeed * _DeltaTime;
	pos += Quintic::EaseIn(mElapseTime, MAttackSpeed * _DeltaTime, differencePos, mTotalAnimTime) * forward;

	_owner->SetPosition(pos);

	// アニメーションが終了したら待機状態へ
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		return EnemyState::eEnemyStateWait;
	}

	return EnemyState::eEnemyStateAttack;
}

void EnemyObjectStateAttack::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateAttack));

	// アニメーション再生時間取得
	mTotalAnimTime = _owner->GetAnimPtr(EnemyState::eEnemyStateAttack)->GetDuration();
	mElapseTime = 0.0f;
}