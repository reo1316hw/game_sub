#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
BossObjectStateFlyingBackDamage::BossObjectStateFlyingBackDamage(PlayerObject* _playerPtr)
	: MHitStopEndTiming(10)
	, MVecShortenVelue(0.1f)
	, MSeparationVecLength(4.0f)
	, MPlayRate(1.5f)
	, MDamageInitSpeed(400.0f)
	, MDecelerationSpeedValue(1.8f)
	, mIsHitStop(false)
	, mHitPoint(0)
	, mHitStopCount(0)
	, mDamageSpeed(0.0f)
	, mDecelerationSpeed(0.0f)
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
	, mDirPlayerVec(Vector3::Zero)
	, mPlayerPtr(_playerPtr)
	, mBoxColliderPtr(nullptr)
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="_owner"> ボス(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
/// <returns> ボスの状態 </returns>
BossState BossObjectStateFlyingBackDamage::Update(BossObject* _owner, const float _DeltaTime)
{
	if (mHitPoint <= 0)
	{
		return BossState::eBossStateDeath;
	}

	++mHitStopCount;

	if (mHitStopCount <= MHitStopEndTiming)
	{
		return BossState::eBossStateFlyingBackDamage;
	}

	// 速度
	Vector3 velocity = mDamageSpeed * mDirPlayerVec;
	mDamageSpeed -= mDecelerationSpeed;
	mDecelerationSpeed += 0.05f;

	if (mDamageSpeed <= 0.0f)
	{
		mDamageSpeed = 0.0f;
	}

	mPosition -= velocity * _DeltaTime;

	_owner->SetPosition(mPosition);

	// アニメーションが終了したら待機状態へ
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		return BossState::eBossStateTeleportation;
	}

	return BossState::eBossStateFlyingBackDamage;
}

/// <summary>
/// ボス同士の引き離し
/// </summary>
/// <param name="_owner"> ボス(親)のポインタ </param>
/// <param name="_DirTargetEnemyVec"> 対象となるエネミーに向いたベクトル </param>
void BossObjectStateFlyingBackDamage::Separation(BossObject* _owner, const Vector3& _DirTargetEnemyVec)
{
	// 座標
	mPosition = _owner->GetPosition();
	// 引き離しベクトル
	Vector3 separationVec = MSeparationVecLength * _DirTargetEnemyVec;

	mVelocity -= separationVec;
	mVelocity *= MVecShortenVelue;
	mPosition += mVelocity;

	_owner->SetPosition(mPosition);
}

/// <summary>
/// ボスの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> ボス(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void BossObjectStateFlyingBackDamage::Enter(BossObject* _owner, const float _DeltaTime)
{
	mBoxColliderPtr = _owner->GetBoxCollider();
	// エネミーの当たり判定を無効にする
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	mIsHitStop = false;

	// プレイヤーのステートが3段階目の通常攻撃状態だったらヒットストップを行う
	if (mPlayerPtr->GetNowState() == PlayerState::ePlayerStateThirdAttack)
	{
		mIsHitStop = true;
	}

	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(BossState::eBossStateFlyingBackDamage), MPlayRate);
	meshcomp->SetIsHitStop(mIsHitStop);

	// ヒットストップするフレーム数を初期化
	mHitStopCount = 0;

	// 座標
	mPosition = _owner->GetPosition();
	// プレイヤーの座標
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// プレイヤーに向いたベクトル
	mDirPlayerVec = playerPos - mPosition;
	mDirPlayerVec.Normalize();

	mDamageSpeed = MDamageInitSpeed;
	mDecelerationSpeed = MDecelerationSpeedValue;

	// ダメージ値
	int damageValue = _owner->GetDamageValue();
	// 体力
	mHitPoint = _owner->GetHitPoint() - damageValue;

	// オブジェクトのスケールサイズを求めるための左辺の値を設定
	_owner->SetScaleLeftSideValue(mHitPoint);
	_owner->RotateToNewForward(mDirPlayerVec);
	_owner->SetHitPoint(mHitPoint);
}

/// <summary>
/// ボスの状態が変更して、最後に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> ボス(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void BossObjectStateFlyingBackDamage::Exit(BossObject* _owner, const float _DeltaTime)
{
	// エネミーの当たり判定を有効にする
	mBoxColliderPtr->SetCollisionState(CollisionState::eEnableCollision);
}