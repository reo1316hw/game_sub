#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_weaponPtr"> プレイヤーの武器のポインタ </param>
PlayerObjectStateThirdAttack::PlayerObjectStateThirdAttack(PlayerWeaponObject* _weaponPtr)
	: MBoxEnableTiming(30)
	, MAttackSpeed(150.0f)
	, MPlayRate(1.5f)
	, mHitUntilCount(0)
	, mOwnerBoxCollider(_weaponPtr->GetBoxCollider())
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
	// 座標
	Vector3 pos = _owner->GetPosition();
	// 前方ベクトル
	Vector3 forward = _owner->GetForward();
	// 開始速度
	float startSpeed = MAttackSpeed * _DeltaTime;
	// 終了速度
	float endSpeed = -MAttackSpeed * _DeltaTime;

	// 攻撃踏み込み移動のためのアニメーション再生時間の経過割合を計算
	mElapseTime += _DeltaTime;
	// 経過割合をもとに移動処理
	pos += Quintic::EaseIn(mElapseTime, startSpeed, endSpeed, mTotalAnimTime) * forward;

	_owner->SetPosition(pos);

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
	else if (mIsHit)
	{
		return PlayerState::ePlayerStateDamage;
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
	// ATTACK3のアニメーション再生
	SkeletalMeshComponent* meshComp = _owner->GetSkeletalMeshComponentPtr();
	meshComp->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateThirdAttack), MPlayRate);
	mIsHit = false;

	// アニメーション再生時間取得
	mTotalAnimTime = _owner->GetAnimPtr(PlayerState::ePlayerStateThirdAttack)->GetDuration() - 0.6f;
	mElapseTime = 0.0f;
	mHitUntilCount = 0;
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
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eEnemyAttackDecision)
	{
		mIsHit = true;
	}
}