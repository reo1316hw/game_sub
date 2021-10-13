#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
EnemyObjectStateWait::EnemyObjectStateWait(PlayerObject* _playerPtr)
	: MTransitionStateDistance(15000.0f)
	, MVecShortenVelue(0.1f)
	, MTransitionTimingNum(120)
	, mIsDamage(false)
	, mTransitionCount(0)
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

	++mTransitionCount;

	if (mTransitionCount >= MTransitionTimingNum)
	{
		// ランダム値
		int randNum = rand() % 90;

		if (randNum < 30)
		{
			return EnemyState::eEnemyStateAttack;
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
	else if (dirPlayerVec.LengthSq() >= MTransitionStateDistance)
	{
		return EnemyState::eEnemyStateTrack;
	}
	else if(mIsDamage)
	{
		return EnemyState::eEnemyStateDamage;
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
	mTransitionCount = 0;
}

/// <summary>
/// エネミー同士の引き離し
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_SeparationVec"> 引き離しベクトル </param>
void EnemyObjectStateWait::Separation(EnemyObject* _owner, const Vector3& _SeparationVec)
{
	/*mVelocity -= _SeparationVec;
	mVelocity *= MVecShortenVelue;

	mPosition += mVelocity;
	_owner->SetPosition(mPosition);*/
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void EnemyObjectStateWait::OnColision(EnemyObject* _owner, const GameObject& _HitObject)
{
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eWeapon)
	{
		mIsDamage = true;
	}
}