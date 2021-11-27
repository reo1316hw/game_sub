#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_enemyAttackPtr"> エネミーの攻撃判定オブジェクトのポインタ </param>
EnemyObjectStateAttack::EnemyObjectStateAttack(EnemyAttackDecisionObject* _enemyAttackPtr)
	: mHitTagList{ Tag::eDashAttackEffect, Tag::eFirstAttackEffect, Tag::eSecondAttackEffect, Tag::eThirdAttackEffect }
	, mDamageValueList{ 10, 5, 15, 25 }
	, MBoxEnableTiming(0.4f)
	, MStateTransitionProbability(100)
	, MAttackSpeed(150.0f)
	, MPlayRate(1.5f)
	, MVecShortenVelue(0.1f)
	, MSeparationVecLength(4.0f)
	, mIsDamage(false)
	, mIsCollisionState(false)
	, mIsOneCollisionState(false)
	, mDamageValue(0)
	, mHitTagListSize(sizeof(mHitTagList) / sizeof(int))
	, mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
	, mBoxDisableTiming(0)
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
	, mForwardVec(Vector3::Zero)
	, mHitTag(Tag::eOther)
	, mEnemyPtr(nullptr)
	, mOwnerBoxCollider(_enemyAttackPtr->GetBoxCollider())
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
/// <returns> エネミーの状態 </returns>
EnemyState EnemyObjectStateAttack::Update(EnemyObject* _owner, const float _DeltaTime)
{
	if (mIsDamage)
	{
		switch (mHitTag)
		{
		case Tag::eDashAttackEffect:

			return EnemyState::eEnemyStateImpactDamage;

		case Tag::eFirstAttackEffect:

			return EnemyState::eEnemyStateImpactDamage;

		case Tag::eSecondAttackEffect:

			return EnemyState::eEnemyStateSweepFallDamage;

		case Tag::eThirdAttackEffect:

			return EnemyState::eEnemyStateFlyingBackDamage;
		}
	}

	// 更新される前の座標
	Vector3 prePosition = mPosition;
	// 開始速度
	float startSpeed = MAttackSpeed * _DeltaTime;
	// 終了速度
	float endSpeed = -MAttackSpeed * _DeltaTime;

	// 攻撃踏み込み移動のためのアニメーション再生時間の経過割合を計算
	mElapseTime += _DeltaTime;
	// 経過割合をもとに移動処理
	mPosition += Quintic::EaseIn(mElapseTime, startSpeed, endSpeed, mTotalAnimTime) * mForwardVec;

	// 速度を計算
	mVelocity = prePosition - mPosition;

	_owner->SetPosition(mPosition);

	// アニメーションが終了したら移動状態へ
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		// ランダム値
		int randNum = rand() % MStateTransitionProbability;
		
		if (randNum < 50)
		{
			return EnemyState::eEnemyStateWait;
		}
		else if(randNum >= 50 && randNum < 80)
		{
			return EnemyState::eEnemyStateLeftMove;
		}
		else
		{
			return EnemyState::eEnemyStateRightMove;
		}
	}

	if (mIsOneCollisionState)
	{
		return EnemyState::eEnemyStateAttack;
	}

	if (mElapseTime >= MBoxEnableTiming)
	{
		// 攻撃の当たり判定を有効にする
		mIsCollisionState = true;
		mOwnerBoxCollider->SetCollisionState(CollisionState::eEnableCollision);
	}

	if (!mIsCollisionState)
	{
		return EnemyState::eEnemyStateAttack;
	}

	mBoxDisableTiming = MBoxEnableTiming + _DeltaTime;

	if (mElapseTime >= mBoxDisableTiming)
	{
		// 攻撃の当たり判定を無効にする
		mIsCollisionState = false;
		mIsOneCollisionState = true;
		mOwnerBoxCollider->SetCollisionState(CollisionState::eDisableCollision);
	}

	return EnemyState::eEnemyStateAttack;
}

/// <summary>
/// エネミーの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void EnemyObjectStateAttack::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateAttack), MPlayRate);

	// アニメーション再生時間取得
	mTotalAnimTime = _owner->GetAnimPtr(EnemyState::eEnemyStateAttack)->GetDuration() - 0.5f;
	mElapseTime = 0.0f;

	mIsDamage = false;
	mIsOneCollisionState = false;

	// 座標
	mPosition = _owner->GetPosition();
	// 前方ベクトル
	mForwardVec = _owner->GetForward();

	_owner->RotateToNewForward(mForwardVec);
}

/// <summary>
/// エネミー同士の引き離し
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DirTargetEnemyVec"> 対象となるエネミーに向いたベクトル </param>
void EnemyObjectStateAttack::Separation(EnemyObject* _owner, const Vector3& _DirTargetEnemyVec)
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
/// ヒットした時の処理
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void EnemyObjectStateAttack::OnCollision(EnemyObject* _owner, const GameObject& _HitObject)
{
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
bool EnemyObjectStateAttack::ReceivedAttack(const Tag& _hitTag, const int& _DamageValuePlayerAttack)
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