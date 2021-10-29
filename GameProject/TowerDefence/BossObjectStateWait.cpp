#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
BossObjectStateWait::BossObjectStateWait(PlayerObject* _playerPtr)
	: MDamageValuePlayerFirstAttack(25)
	, MTransitionStateDistance(30000.0f)
	, MVecShortenVelue(0.1f)
	, MTransitionTimingNum(120)
	, MSeparationVecLength(8.0f)
	, mIsDamage(false)
	, mDamageValue(0)
	, mPeriodWaitCount(0)
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
	, mPlayerPtr(_playerPtr)
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="_owner"> ボス(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
/// <returns> ボスの状態 </returns>
BossState BossObjectStateWait::Update(BossObject* _owner, const float _DeltaTime)
{
	// プレイヤーの座標
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// プレイヤーに向いたベクトルsd
	Vector3 dirPlayerVec = playerPos - mPosition;

	++mPeriodWaitCount;

	if (mIsDamage)
	{
		return BossState::eBossStateDamage;
	}

	if (mPeriodWaitCount >= MTransitionTimingNum)
	{
		// ランダム値
		int randNum = rand() % 100;

		if (dirPlayerVec.LengthSq() < MTransitionStateDistance)
		{
			if (randNum < 25)
			{
				return BossState::eBossStateAreaAttack;
			}
			else if (randNum >= 25 && randNum < 50)
			{
				return BossState::eBossStateFrontAttack;
			}
			else if (randNum >= 50 && randNum < 75)
			{
				return BossState::eBossStateOverheadAttack;
			}
			else
			{
				return BossState::eBossStateTeleportation;
			}
		}

		if (randNum < 30)
		{
			return BossState::eBossStateFrontAttack;
		}
		else if (randNum >= 30 && randNum < 60)
		{
			return BossState::eBossStateOverheadAttack;
		}
		else
		{
			return BossState::eBossStateTeleportation;
		}
	}

	dirPlayerVec.Normalize();
	_owner->RotateToNewForward(dirPlayerVec);

	return BossState::eBossStateWait;
}

/// <summary>
/// ボスの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> ボス(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void BossObjectStateWait::Enter(BossObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(BossState::eBossStateWait));

	mIsDamage = false;
	mPeriodWaitCount = 0;

	// 座標
	mPosition = _owner->GetPosition();
}

/// <summary>
/// ボスとエネミーの引き離し
/// </summary>
/// <param name="_owner"> ボス(親)のポインタ </param>
/// <param name="_DirTargetEnemyVec"> 対象となるエネミーに向いたベクトル </param>
void BossObjectStateWait::Separation(BossObject* _owner, const Vector3& _DirTargetEnemyVec)
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
/// <param name="_owner"> ボス(親)のポインタ </param>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void BossObjectStateWait::OnCollision(BossObject* _owner, const GameObject& _HitObject)
{
	// オブジェクトのタグ
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eFirstAttackEffect)
	{
		mDamageValue = MDamageValuePlayerFirstAttack;
		mIsDamage = true;
	}

	if (tag == Tag::eSecondAttackEffect)
	{
		mDamageValue = MDamageValuePlayerFirstAttack;
		mIsDamage = true;
	}

	if (tag == Tag::eThirdAttackEffect)
	{
		mDamageValue = MDamageValuePlayerFirstAttack;
		mIsDamage = true;
	}

	_owner->SetDamageValue(mDamageValue);
}