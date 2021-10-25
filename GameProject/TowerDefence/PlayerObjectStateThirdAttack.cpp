#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_weaponPtr"> プレイヤーの武器のポインタ </param>
PlayerObjectStateThirdAttack::PlayerObjectStateThirdAttack(PlayerWeaponObject* _weaponPtr)
	: MBoxEnableTiming(30)
	, MDamageValueEnemyAttack(25)
	, MHitStopEndTiming(10)
	, MAttackSpeed(150.0f)
	, MPlayRate(1.5f)
	, mIsHitStop(false)
	, mDamageValue(0)
	, mHitUntilCount(0)
	, mHitStopCount(0)
	, mPosition(Vector3::Zero)
	, mForwardVec(Vector3::Zero)
	, mOwnerBoxCollider(_weaponPtr->GetBoxCollider())
	, mWeaponPtr(_weaponPtr)
	, skeletalMeshCompPtr(nullptr)
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
/// <returns> プレイヤーの状態 </returns>
PlayerState PlayerObjectStateThirdAttack::Update(PlayerObject* _owner, const float _DeltaTime)
{
	if (mIsHit)
	{
		return PlayerState::ePlayerStateDamage;
	}

	// 攻撃時に武器が当たったらヒットストップを行う
	if (mWeaponPtr->IsHitCheck())
	{
		mIsHitStop = true;
		skeletalMeshCompPtr->SetIsHitStop(mIsHitStop);
	}

	// ヒットストップ時に移動処理を無効化
	if (mIsHitStop)
	{
		++mHitStopCount;

		if (mHitStopCount <= MHitStopEndTiming)
		{
			return PlayerState::ePlayerStateThirdAttack;
		}

		mIsHitStop = false;
		mHitStopCount = 0;
	}

	// 開始速度
	float startSpeed = MAttackSpeed * _DeltaTime;
	// 終了速度
	float endSpeed = -MAttackSpeed * _DeltaTime;

	// 攻撃踏み込み移動のためのアニメーション再生時間の経過割合を計算
	mElapseTime += _DeltaTime;
	// 経過割合をもとに移動処理
	mPosition += Quintic::EaseIn(mElapseTime, startSpeed, endSpeed, mTotalAnimTime) * mForwardVec;

	_owner->SetPosition(mPosition);

	++mHitUntilCount;

	if (mHitUntilCount == MBoxEnableTiming)
	{
		// 武器の当たり判定を行うようにする
		mOwnerBoxCollider->SetCollisionState(CollisionState::eEnableCollision);
	}

	// アニメーションが終了したらcStopTime硬直後、IDLE状態へ
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		return PlayerState::ePlayerStateIdle;
	}

	return PlayerState::ePlayerStateThirdAttack;
}

/// <summary>
/// プレイヤーの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void PlayerObjectStateThirdAttack::Enter(PlayerObject* _owner, const float _DeltaTime)
{
	// 3段階目の通常攻撃状態のアニメーション再生
	skeletalMeshCompPtr = _owner->GetSkeletalMeshComponentPtr();
	skeletalMeshCompPtr->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateThirdAttack), MPlayRate);
	mIsHit = false;

	// アニメーション再生時間取得
	mTotalAnimTime = _owner->GetAnimPtr(PlayerState::ePlayerStateThirdAttack)->GetDuration() - 0.6f;
	mElapseTime = 0.0f;
	mHitUntilCount = 0;

	// ヒットストップ関係初期化
	mIsHitStop = false;
	mHitStopCount = 0;

	// 座標
	mPosition = _owner->GetPosition();
	// 前方ベクトル
	mForwardVec = _owner->GetForward();
}

/// <summary>
/// プレイヤーの状態が変更して、最後に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void PlayerObjectStateThirdAttack::Exit(PlayerObject* _owner, const float _DeltaTime)
{
	// 武器の当たり判定を行わないようにする
	mOwnerBoxCollider->SetCollisionState(CollisionState::eDisableCollision);
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void PlayerObjectStateThirdAttack::OnCollision(PlayerObject* _owner, const GameObject& _HitObject)
{
	// オブジェクトのタグ
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eEnemyAttackDecision)
	{
		mDamageValue = MDamageValueEnemyAttack;
		mIsHit = true;
	}

	_owner->SetDamageValue(mDamageValue);
}