#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
EnemyObjectStateDeath::EnemyObjectStateDeath(PlayerObject* _playerPtr)
	: MPlayRate(1.5f)
	, MDecelerationSpeed(1.8f)
	, mDeathSpeed(200.0f)
	, mPlayerPtr(_playerPtr)
	, mPosition(Vector3::Zero)
	, mInitPosition(Vector3::Zero)
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
	// 速度
	Vector3 velocity = mDeathSpeed * mDirPlayerVec;
	mDeathSpeed -= MDecelerationSpeed;

	if (mDeathSpeed <= 0.0f)
	{
		mDeathSpeed = 0.0f;
	}

	mPosition -= velocity * _DeltaTime;

	_owner->SetPosition(mPosition);

	// アニメーションが終了したら更新を止める
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		// hpゲージ
		mEnemyHitPointGaugePtr = _owner->GetEnemyHitPointGaugePtr();
		// hpの枠
		mEnemyHitPointFramePtr = _owner->GetEnemyHitPointFramePtr();

		mEnemyHitPointGaugePtr->SetState(State::eDead);
		mEnemyHitPointFramePtr->SetState(State::eDead);
		_owner->SetState(State::eDead);
		_owner->SetPosition(mInitPosition);

		return EnemyState::eEnemyStateTrack;
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

	// 座標
	mPosition = _owner->GetPosition();
	// 初期座標
	mInitPosition = _owner->GetInitPosition();
	// プレイヤーの座標
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// プレイヤーに向いたベクトル
	mDirPlayerVec = playerPos - mPosition;
	mDirPlayerVec.Normalize();

	mDeathSpeed = 200.0f;

	_owner->RotateToNewForward(mDirPlayerVec);
}