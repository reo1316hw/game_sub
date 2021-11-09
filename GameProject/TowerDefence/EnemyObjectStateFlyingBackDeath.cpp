#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
EnemyObjectStateFlyingBackDeath::EnemyObjectStateFlyingBackDeath(PlayerObject* _playerPtr)
	: MHitStopEndTiming(10)
	, MPlayRate(1.5f)
	, MDeathInitSpeed(0.0f)
	, MDecelerationSpeedValue(0.0f)
	, mIsHitStop(false)
	, mHitStopCount(0)
	, mDeathSpeed(0.0f)
	, mDecelerationSpeed(0.0f)
	, mPosition(Vector3::Zero)
	, mInitPosition(Vector3::Zero)
	, mDirPlayerVec(Vector3::Zero)
	, mPlayerPtr(_playerPtr)
	, mEnemyHitPointGaugePtr(nullptr)
	, mEnemyHitPointFramePtr(nullptr)
	, mBoxColliderPtr(nullptr)
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
/// <returns> エネミーの状態 </returns>
EnemyState EnemyObjectStateFlyingBackDeath::Update(EnemyObject* _owner, const float _DeltaTime)
{
	++mHitStopCount;

	if (mHitStopCount <= MHitStopEndTiming)
	{
		return EnemyState::eEnemyStateFlyingBackDeath;
	}

	// 速度
	Vector3 velocity = mDeathSpeed * mDirPlayerVec;
	mDeathSpeed -= mDecelerationSpeed;
	mDecelerationSpeed += 0.05f;

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
		//mEnemyHitPointFramePtr = _owner->GetEnemyHitPointFramePtr();

		mEnemyHitPointGaugePtr->SetState(State::eDead);
		//mEnemyHitPointFramePtr->SetState(State::eDead);
		_owner->SetHitPoint(_owner->GetMaxHp());
		_owner->SetState(State::eDead);
		_owner->SetPosition(mInitPosition);

		return EnemyState::eEnemyStateTrack;
	}

	return EnemyState::eEnemyStateFlyingBackDeath;
}

/// <summary>
/// エネミーの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void EnemyObjectStateFlyingBackDeath::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	mBoxColliderPtr = _owner->GetBoxCollider();
	// エネミーの当たり判定を無効にする
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	mIsHitStop = false;

	// プレイヤーのステートが3段階目の通常攻撃状態だったらヒットストップを行う
	if (mPlayerPtr->GetPlayerState() == PlayerState::ePlayerStateThirdAttack)
	{
		mIsHitStop = true;
	}

	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateFlyingBackDeath), MPlayRate);
	meshcomp->SetIsHitStop(mIsHitStop);

	// ヒットストップするフレーム数を初期化
	mHitStopCount = 0;

	// 座標
	mPosition = _owner->GetPosition();
	// 初期座標
	mInitPosition = _owner->GetInitPosition();
	// プレイヤーの座標
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// プレイヤーに向いたベクトル
	mDirPlayerVec = playerPos - mPosition;
	mDirPlayerVec.Normalize();

	mDeathSpeed = 400.0f;
	mDecelerationSpeed = 1.8f;

	_owner->RotateToNewForward(mDirPlayerVec);
}

/// <summary>
/// エネミーの状態が変更して、最後に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void EnemyObjectStateFlyingBackDeath::Exit(EnemyObject* _owner, const float _DeltaTime)
{
	// エネミーの当たり判定を有効にする
	mBoxColliderPtr->SetCollisionState(CollisionState::eEnableCollision);
}