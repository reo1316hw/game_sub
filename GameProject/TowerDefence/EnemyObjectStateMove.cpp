#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
EnemyObjectStateMove::EnemyObjectStateMove(PlayerObject* _playerPtr)
	: MTransitionTimingNum(120)
	, MTransitionStateDistance(15000.0f)
	, mIsDamage(false)
	, mIsMoving(false)
	, mMoveSpeed(1.0f)
	, mPeriodMoveCount(0)
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
	Vector3 pos = _owner->GetPosition();
	// 右方ベクトル
	Vector3 rightVec = _owner->GetRight();
	rightVec.z = 0.0f;


	// ランダム値
	int randNum = rand() % 100;

	if (!mIsMoving)
	{
		// 逆向きのベクトルに変換
		if (randNum < 50)
		{
			mIsMoving = true;
		}
		else
		{
			mIsMoving = true;
			mMoveSpeed *= -1.0f;
		}
	}
	else
	{
		++mPeriodMoveCount;
	}

	// プレイヤーの座標
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// プレイヤーに向いたベクトル
	Vector3 dirPlayerVec = playerPos - pos;
	dirPlayerVec.Normalize();
	_owner->RotateToNewForward(dirPlayerVec);

	// 速度ベクトル
	Vector3 vel = mMoveSpeed * rightVec;
	pos += vel;
	_owner->SetPosition(pos);

	if (mPeriodMoveCount >= MTransitionTimingNum)
	{
		mIsMoving = false;

		if (dirPlayerVec.LengthSq() >= MTransitionStateDistance)
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
	else if (mIsDamage)
	{
		return EnemyState::eEnemyStateDamage;
	}

	return EnemyState::eEnemyStateMove;
}

/// <summary>
/// エネミーの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void EnemyObjectStateMove::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateMove));

	mIsDamage = false;
	mPeriodMoveCount = 0;
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void EnemyObjectStateMove::OnColision(const GameObject& _HitObject)
{
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eWeapon)
	{
		mIsDamage = true;
	}
}