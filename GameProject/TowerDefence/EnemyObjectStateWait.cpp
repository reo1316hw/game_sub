#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
EnemyObjectStateWait::EnemyObjectStateWait(PlayerObject* _playerPtr)
	: MTransitionTimingNum(120)
	, MStateTransitionProbability(100)
	, MDamageValuePlayerFirstAttack(25)
	, MTransitionStateShortDistance(15000.0f)
	, MTransitionStateMediumDistance(30000.0f)
	, MVecShortenVelue(0.1f)
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
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
/// <returns> エネミーの状態 </returns>
EnemyState EnemyObjectStateWait::Update(EnemyObject* _owner, const float _DeltaTime)
{
	// 座標
	mPosition = _owner->GetPosition();
	// プレイヤーの座標
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// プレイヤーに向いたベクトルsd
	Vector3 dirPlayerVec = playerPos - mPosition;

	++mPeriodWaitCount;

	if (mIsDamage)
	{
		return EnemyState::eEnemyStateDamage;
	}

	if (mPeriodWaitCount >= MTransitionTimingNum)
	{
		// ランダム値
		int randNum = rand() % MStateTransitionProbability;

		if (dirPlayerVec.LengthSq() < MTransitionStateShortDistance)
		{
			if (randNum < 25)
			{
				return EnemyState::eEnemyStateWait;
			}
			else if(randNum >= 25 && randNum < 50)
			{
				return EnemyState::eEnemyStateLeftMove;
			}
			else if (randNum >= 50 && randNum < 75)
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
			if (randNum < 30)
			{
				return EnemyState::eEnemyStateWait;
			}
			else if (randNum >= 30 && randNum < 60)
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
	// オブジェクトのタグ
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eDashAttackEffect)
	{
		mDamageValue = MDamageValuePlayerFirstAttack;
		mIsDamage = true;
		return;
	}

	if (tag == Tag::eFirstAttackEffect)
	{
		mDamageValue = MDamageValuePlayerFirstAttack;
		mIsDamage = true;
		return;
	}

	if (tag == Tag::eSecondAttackEffect)
	{
		mDamageValue = MDamageValuePlayerFirstAttack;
		mIsDamage = true;
		return;
	}

	if (tag == Tag::eThirdAttackEffect)
	{
		mDamageValue = MDamageValuePlayerFirstAttack;
		mIsDamage = true;
		return;
	}

	_owner->SetDamageValue(mDamageValue);
}