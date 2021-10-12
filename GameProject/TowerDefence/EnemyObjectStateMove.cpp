#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_State"> エネミーの状態 </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
EnemyObjectStateMove::EnemyObjectStateMove(const EnemyState& _State, PlayerObject* _playerPtr)
	: MTransitionTimingNum(120)
	, MTransitionStateDistance(15000.0f)
	, mIsMoving(false)
	, mIsDamage(false)
	, mIsHitEnemy(false)
	, mMoveSpeed(1.0f)
	, mPeriodMoveCount(0)
	, mEnemyState(_State)
	, mPlayerPtr(_playerPtr)
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
/// <returns> エネミーの状態 </returns>
EnemyState EnemyObjectStateMove::Update(EnemyObject* _owner, const float _DeltaTime)
{
	// 座標
	Vector3 position = _owner->GetPosition();
	// 右方ベクトル
	Vector3 rightVec = _owner->GetRight();
	rightVec.z = 0.0f;

	// プレイヤーの座標
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// プレイヤーに向いたベクトル
	Vector3 dirPlayerVec = playerPos - position;

	if (mEnemyState == EnemyState::eEnemyStateLeftMove)
	{
		rightVec *= -1.0f;
	}

	// 速度ベクトル
	Vector3 vel = mMoveSpeed * rightVec;
	position += vel;
	_owner->SetPosition(position);
    
	++mPeriodMoveCount;

	if (mPeriodMoveCount >= MTransitionTimingNum)
	{
		if (dirPlayerVec.LengthSq() <= MTransitionStateDistance)
		{
			// ランダム値
		    int randNum = rand() % 100;
		    
		    if (randNum < 50)
		    {
		    	return EnemyState::eEnemyStateWait;
		    }
		    else
		    {
		    	return EnemyState::eEnemyStateAttack;
		    }
		}

		return EnemyState::eEnemyStateTrack;
	}
	else
	{
		if (mIsDamage)
		{
			return EnemyState::eEnemyStateDamage;
		}

		if (mIsHitEnemy)
		{
			// ランダム値
			int randNum = rand() % 100;

			if (randNum < 50)
			{
				return EnemyState::eEnemyStateWait;
			}
			else
			{
				if (mEnemyState == EnemyState::eEnemyStateLeftMove)
				{
					return EnemyState::eEnemyStateRightMove;
				}
				else
				{
					return EnemyState::eEnemyStateLeftMove;
				}
			}
		}
	}

	dirPlayerVec.Normalize();
	_owner->RotateToNewForward(dirPlayerVec);

	return mEnemyState;
}

/// <summary>
/// エネミーの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void EnemyObjectStateMove::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(mEnemyState));

	mIsDamage = false;
	mIsHitEnemy = false;
	mPeriodMoveCount = 0;
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void EnemyObjectStateMove::OnColision(EnemyObject* _owner, const GameObject& _HitObject)
{
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eWeapon)
	{
		mIsDamage = true;
	}

	if (tag == Tag::eStopLateralMoveEnemy)
	{
		mIsHitEnemy = true;
	}
}