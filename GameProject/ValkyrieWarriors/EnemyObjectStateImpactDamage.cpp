#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
EnemyObjectStateImpactDamage::EnemyObjectStateImpactDamage(PlayerObject* _playerPtr)
	: mHitTagList{ Tag::eDashAttackEffect, Tag::eFirstAttackEffect, Tag::eSecondAttackEffect, Tag::eThirdAttackEffect }
	, mDamageValueList{ 10, 5, 15, 25 }
	, MDamageSpeed(100.0f)
	, MVecShortenVelue(0.1f)
	, MSeparationVecLength(4.0f)
	, MNotHitTime(0.1f)
	, mIsDamage(false)
	, mHitPoint(0)
	, mDamageValue(0)
	, mHitTagListSize(sizeof(mHitTagList) / sizeof(int))
	, mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
	, mDirPlayerVec(Vector3::Zero)
	, mHitTag(Tag::eOther)
	, mEnemyPtr(nullptr)
	, mPlayerPtr(_playerPtr)
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
/// <returns> エネミーの状態 </returns>
EnemyState EnemyObjectStateImpactDamage::Update(EnemyObject* _owner, const float _DeltaTime)
{
	if (mHitPoint <= 0)
	{
		return EnemyState::eEnemyStateFallingBackDeath;
	}

	if (mIsDamage)
	{
		switch (mHitTag)
		{
		case Tag::eFirstAttackEffect:

			Enter(_owner, _DeltaTime);
			break;

		case Tag::eSecondAttackEffect:

			return EnemyState::eEnemyStateSweepFallDamage;
		}
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
		return EnemyState::eEnemyStateWait;
	}

	return EnemyState::eEnemyStateImpactDamage;
}

/// <summary>
/// エネミー同士の引き離し
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DirTargetEnemyVec"> 対象となるエネミーに向いたベクトル </param>
void EnemyObjectStateImpactDamage::Separation(EnemyObject* _owner, const Vector3& _DirTargetEnemyVec)
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
/// エネミーの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void EnemyObjectStateImpactDamage::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	mIsDamage = false;

	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateImpactDamage));

	// アニメーション再生時間取得
	mTotalAnimTime = _owner->GetAnimPtr(EnemyState::eEnemyStateImpactDamage)->GetDuration();
	mElapseTime = 0.0f;

	// 座標
	mPosition = _owner->GetPosition();
	// プレイヤーの座標
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// プレイヤーに向いたベクトル
	mDirPlayerVec = playerPos - mPosition;
	mDirPlayerVec.Normalize();

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
/// ヒットした時の処理
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void EnemyObjectStateImpactDamage::OnCollision(EnemyObject* _owner, const GameObject& _HitObject)
{
	if (mElapseTime <= MNotHitTime)
	{
		return;
	}

	mEnemyPtr = _owner;
	// 座標
	mPosition = mEnemyPtr->GetPosition();

	// オブジェクトのタグ
	mHitTag = _HitObject.GetTag();

	for (int i = 0; i < mHitTagListSize; i++)
	{
		// 攻撃を受けた時の処理
		if (ReceivedAttack(mHitTagList[i], mDamageValueList[i]))
		{
			return;
		}
	}
}

/// <summary>
/// 攻撃を受けた時の処理
/// </summary>
/// <param name="_HitTag"> ヒットしたオブジェクトのタグ </param>
/// <param name="_DamageValuePlayerAttack"> ダメージ量 </param>
/// <returns> ヒットしたか </returns>
bool EnemyObjectStateImpactDamage::ReceivedAttack(const Tag& _hitTag, const int& _DamageValuePlayerAttack)
{
	if (mHitTag == _hitTag)
	{
		mDamageValue = _DamageValuePlayerAttack;
		mIsDamage = true;

		mEnemyPtr->SetDamageValue(mDamageValue);
		return true;
	}

	return false;
}