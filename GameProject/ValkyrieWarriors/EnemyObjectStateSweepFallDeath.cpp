#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
EnemyObjectStateSweepFallDeath::EnemyObjectStateSweepFallDeath(PlayerObject* _playerPtr)
	: MVecShortenVelue(0.1f)
	, MSeparationVecLength(4.0f)
	, MDeathInitSpeed(100.0f)
	, MGravity(4.0f)
	, mHitPoint(0)
	, mDeathSpeed(0.0f)
	, mPosition(Vector3::Zero)
	, mInitPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
	, mDirPlayerVec(Vector3::Zero)
	, mPlayerPtr(_playerPtr)
	, mEnemyHitPointGaugePtr(nullptr)
	, mEnemyHitPointFramePtr(nullptr)
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
/// <returns> エネミーの状態 </returns>
EnemyState EnemyObjectStateSweepFallDeath::Update(EnemyObject* _owner, const float _DeltaTime)
{
	// 速度
	Vector3 velocity = mDeathSpeed * Vector3::UnitZ;
	mDeathSpeed -= MGravity;

	mPosition += velocity * _DeltaTime;

	if (mPosition.z <= mNowStateInitPos.z)
	{
		mPosition.z = mNowStateInitPos.z;
	}

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

		_owner->SetHitPoint(_owner->GetMaxHp());
		_owner->SetScaleLeftSideValue(_owner->GetMaxHp());
		_owner->SetState(State::eDead);
		_owner->SetPosition(mInitPosition);

		return EnemyState::eEnemyStateTrack;
	}

	return EnemyState::eEnemyStateSweepFallDeath;
}

/// <summary>
/// エネミーの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void EnemyObjectStateSweepFallDeath::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateSweepFallDeath));

	mDeathSpeed = MDeathInitSpeed;

	// 座標
	mPosition = _owner->GetPosition();
	// このステートに入った時の座標
	mNowStateInitPos = mPosition;
	// 初期座標
	mInitPosition = _owner->GetInitPosition();
	// プレイヤーの座標
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// プレイヤーに向いたベクトル
	mDirPlayerVec = playerPos - mPosition;
	mDirPlayerVec.Normalize();

	_owner->RotateToNewForward(mDirPlayerVec);
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void EnemyObjectStateSweepFallDeath::OnCollision(EnemyObject* _owner, const GameObject& _HitObject)
{
	// 座標
	mPosition = _owner->GetPosition();
}