#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
EnemyObjectStateDamage::EnemyObjectStateDamage()
    : MDamageSpeed(100.0f)
	, mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
/// <returns> エネミーの状態 </returns>
EnemyState EnemyObjectStateDamage::Update(EnemyObject* _owner, const float _DeltaTime)
{
	// 座標
	Vector3 position = _owner->GetPosition();
	// 前方ベクトル
	Vector3 forward = _owner->GetForward();
	// 開始速度
	float startSpeed = -MDamageSpeed * _DeltaTime;
	// 終了速度
	float endSpeed = MDamageSpeed * _DeltaTime;

	// 攻撃踏み込み移動のためのアニメーション再生時間の経過割合を計算
	mElapseTime += _DeltaTime;
	// 経過割合をもとに移動処理
	position += Quintic::EaseIn(mElapseTime, startSpeed, endSpeed, mTotalAnimTime) * forward;

	_owner->SetPosition(position);
	
	// アニメーションが終了したら待機状態へ
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		return EnemyState::eEnemyStateDeath;
	}

	return EnemyState::eEnemyStateDamage;
}

/// <summary>
/// エネミーの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void EnemyObjectStateDamage::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateDamage));

	// アニメーション再生時間取得
	mTotalAnimTime = _owner->GetAnimPtr(EnemyState::eEnemyStateAttack)->GetDuration();

	mElapseTime = 0.0f;
}