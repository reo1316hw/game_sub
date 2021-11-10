#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
EnemyObjectStateFallingBackDeath::EnemyObjectStateFallingBackDeath(PlayerObject* _playerPtr)
	: MDamageSpeed(50.0f)
	, MPlayRate(1.0f)
	, mIsHitStop(false)
	, mHitStopCount(0)
	, MHitStopEndTiming(5)
	, mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
	, mPosition(Vector3::Zero)
	, mInitPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
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
EnemyState EnemyObjectStateFallingBackDeath::Update(EnemyObject* _owner, const float _DeltaTime)
{
	++mHitStopCount;

	if (mHitStopCount <= MHitStopEndTiming)
	{
		return EnemyState::eEnemyStateFallingBackDeath;
	}

	// 開始速度
	float startSpeed = -MDamageSpeed * _DeltaTime;
	// 終了速度
	float endSpeed = MDamageSpeed * _DeltaTime;

	// 攻撃踏み込み移動のためのアニメーション再生時間の経過割合を計算
	mElapseTime += _DeltaTime;
	// 経過割合をもとに移動処理
	mPosition += Quintic::EaseIn(mElapseTime, startSpeed, endSpeed, mTotalAnimTime) * mDirPlayerVec;

	_owner->SetPosition(mPosition);

	// アニメーションが終了したら待機状態へ
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

	return EnemyState::eEnemyStateFallingBackDeath;
}

/// <summary>
/// エネミーの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void EnemyObjectStateFallingBackDeath::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	mBoxColliderPtr = _owner->GetBoxCollider();
	// エネミーの当たり判定を無効にする
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	mIsHitStop = false;

	// プレイヤーのステートがダッシュ攻撃状態だったらヒットストップを行う
	if (mPlayerPtr->GetPlayerState() == PlayerState::ePlayerStateDashAttack)
	{
		mIsHitStop = true;
	}

	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateFallingBackDeath), MPlayRate, MHitStopEndTiming);
	meshcomp->SetIsHitStop(mIsHitStop);

	// アニメーション再生時間取得
	mTotalAnimTime = _owner->GetAnimPtr(EnemyState::eEnemyStateFallingBackDeath)->GetDuration() - 0.3f;
	mElapseTime = 0.0f;

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

	_owner->RotateToNewForward(mDirPlayerVec);
}

/// <summary>
/// エネミーの状態が変更して、最後に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void EnemyObjectStateFallingBackDeath::Exit(EnemyObject* _owner, const float _DeltaTime)
{
	// エネミーの当たり判定を有効にする
	mBoxColliderPtr->SetCollisionState(CollisionState::eEnableCollision);
}