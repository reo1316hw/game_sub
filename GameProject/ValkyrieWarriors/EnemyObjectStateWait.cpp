#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
EnemyObjectStateWait::EnemyObjectStateWait(PlayerObject* _playerPtr)
	: mHitTagList{ Tag::eDashAttackEffect, Tag::eFirstAttackEffect, Tag::eSecondAttackEffect, Tag::eThirdAttackEffect }
	, mDamageValueList{ 10, 5, 15, 25 }
	, MTransitionTimingNum(120)
	, MStateTransitionProbability(100)
	, MTransitionStateShortDistance(15000.0f)
	, MTransitionStateMediumDistance(30000.0f)
	, MVecShortenVelue(0.1f)
	, MSeparationVecLength(8.0f)
	, mIsDamage(false)
	, mDamageValue(0)
	, mPeriodWaitCount(0)
	, mHitTagListSize(sizeof(mHitTagList) / sizeof(int))
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
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
EnemyState EnemyObjectStateWait::Update(EnemyObject* _owner, const float _DeltaTime)
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

	// 座標
	mPosition = _owner->GetPosition();
	// プレイヤーの座標
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// プレイヤーに向いたベクトル
	Vector3 dirPlayerVec = playerPos - mPosition;

	++mPeriodWaitCount;

	if (mPeriodWaitCount >= MTransitionTimingNum)
	{
		// ランダム値
		int randNum = rand() % MStateTransitionProbability;

		if (dirPlayerVec.LengthSq() < MTransitionStateShortDistance)
		{
			if (randNum < 50)
			{
				return EnemyState::eEnemyStateWait;
			}
			else if(randNum >= 50 && randNum < 65)
			{
				return EnemyState::eEnemyStateLeftMove;
			}
			else if (randNum >= 65 && randNum < 80)
			{
				return EnemyState::eEnemyStateRightMove;
			}
			else
			{
				return EnemyState::eEnemyStateAttackReady;
			}
		}
		else if (dirPlayerVec.LengthSq() >= MTransitionStateShortDistance &&
			     dirPlayerVec.LengthSq() < MTransitionStateMediumDistance)
		{
			if (randNum < 50)
			{
				return EnemyState::eEnemyStateWait;
			}
			else if (randNum >= 50 && randNum < 80)
			{
				return EnemyState::eEnemyStateLeftMove;
			}
			else
			{
				return EnemyState::eEnemyStateRightMove;
			}
		}

		return EnemyState::eEnemyStateTrack;
	}

	dirPlayerVec.Normalize();
	_owner->RotateToNewForward(dirPlayerVec);

	return EnemyState::eEnemyStateWait;
}

/// <summary>
/// エネミーの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void EnemyObjectStateWait::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateWait));

	mIsDamage = false;
	mPeriodWaitCount = 0;
}

/// <summary>
/// エネミー同士の引き離し
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DirTargetEnemyVec"> 対象となるエネミーに向いたベクトル </param>
void EnemyObjectStateWait::Separation(EnemyObject* _owner, const Vector3& _DirTargetEnemyVec)
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
void EnemyObjectStateWait::OnCollision(EnemyObject* _owner, const GameObject& _HitObject)
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
bool EnemyObjectStateWait::ReceivedAttack(const Tag& _hitTag, const int& _DamageValuePlayerAttack)
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