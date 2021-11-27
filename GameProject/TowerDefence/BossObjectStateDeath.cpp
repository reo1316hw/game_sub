#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
BossObjectStateDeath::BossObjectStateDeath(PlayerObject* _playerPtr)
	: MMovingTiming(100)
	, MDamageSpeed(50.0f)
	, MVecShortenVelue(0.1f)
	, MSeparationVecLength(4.0f)
	, mMoveUntilCount(0)
	, mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
	, mDirPlayerVec(Vector3::Zero)
	, mPlayerPtr(_playerPtr)
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="_owner"> ボス(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
/// <returns> ボスの状態 </returns>
BossState BossObjectStateDeath::Update(BossObject* _owner, const float _DeltaTime)
{
	++mMoveUntilCount;

	if (mMoveUntilCount >= MMovingTiming)
	{
		// 開始速度
		float startSpeed = -MDamageSpeed * _DeltaTime;
		// 終了速度
		float endSpeed = MDamageSpeed * _DeltaTime;

		// 攻撃踏み込み移動のためのアニメーション再生時間の経過割合を計算
		mElapseTime += _DeltaTime;
		// 経過割合をもとに移動処理
		mPosition += Quintic::EaseIn(mElapseTime, startSpeed, endSpeed, mTotalAnimTime) * mDirPlayerVec;

		_owner->SetPosition(mPosition);
	}

	// アニメーションが終了したら待機状態へ
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		_owner->SetState(State::eDead);
	}

	return BossState::eBossStateDeath;
}

/// <summary>
/// ボスとエネミーの引き離し
/// </summary>
/// <param name="_owner"> ボス親)のポインタ </param>
/// <param name="_DirTargetEnemyVec"> 対象となるエネミーに向いたベクトル </param>
void BossObjectStateDeath::Separation(BossObject* _owner, const Vector3& _DirTargetEnemyVec)
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
/// <param name="_owner"> ボス親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void BossObjectStateDeath::Enter(BossObject* _owner, const float _DeltaTime)
{
	// ボックスの当たり判定を行うコンポーネントクラスのポインタ
	BoxCollider* boxColliderPtr = _owner->GetBoxCollider();
	// エネミーの当たり判定を無効にする
	boxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(BossState::eBossStateDeath));

	// アニメーション再生時間取得
	mTotalAnimTime = _owner->GetAnimPtr(BossState::eBossStateDeath)->GetDuration()- 1.5f;
	mElapseTime = 0.0f;
	mMoveUntilCount = 0;

	// 座標
	mPosition = _owner->GetPosition();
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
/// <param name="_owner"> ボス(親)のポインタ </param>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void BossObjectStateDeath::OnCollision(BossObject* _owner, const GameObject& _HitObject)
{
	// 座標
	mPosition = _owner->GetPosition();
}