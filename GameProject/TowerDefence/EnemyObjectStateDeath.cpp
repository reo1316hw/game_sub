#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
EnemyObjectStateDeath::EnemyObjectStateDeath(PlayerObject* _playerPtr)
	: MPlayRate(1.5f)
	, MDeathSpeed(150.0f)
	, mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
	, mPlayerPtr(_playerPtr)
	, mPosition(Vector3::Zero)
	, mDirPlayerVec(Vector3::Zero)
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
/// <returns> エネミーの状態 </returns>
EnemyState EnemyObjectStateDeath::Update(EnemyObject* _owner, const float _DeltaTime)
{
	// 開始速度
	float startSpeed = -MDeathSpeed * _DeltaTime;
	// 終了速度
	float endSpeed = MDeathSpeed * _DeltaTime;

	// 攻撃踏み込み移動のためのアニメーション再生時間の経過割合を計算
	mElapseTime += _DeltaTime;
	// 経過割合をもとに移動処理
	mPosition += Quintic::EaseIn(mElapseTime, startSpeed, endSpeed, mTotalAnimTime) * mDirPlayerVec;

	_owner->SetPosition(mPosition);

	// アニメーションが終了したら更新を止める
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		_owner->SetState(State::eDead);
	}

	return EnemyState::eEnemyStateDeath;
}

/// <summary>
/// エネミーの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void EnemyObjectStateDeath::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateDeath), MPlayRate);
	// アニメーション再生時間取得
	mTotalAnimTime = _owner->GetAnimPtr(EnemyState::eEnemyStateAttack)->GetDuration() - 4.5f;
	mElapseTime = 0.0f;

	// 座標
	mPosition = _owner->GetPosition();
	// プレイヤーの座標
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// プレイヤーに向いたベクトル
	mDirPlayerVec = playerPos - mPosition;
	mDirPlayerVec.Normalize();

	_owner->RotateToNewForward(mDirPlayerVec);
}