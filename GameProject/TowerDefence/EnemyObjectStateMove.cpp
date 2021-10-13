#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_State"> エネミーの状態 </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
EnemyObjectStateMove::EnemyObjectStateMove(const EnemyState& _State, PlayerObject* _playerPtr)
	: MTransitionTimingNum(120)
	, MTransitionStateDistance(30000.0f)
	, MVecShortenVelue(0.1f)
	, MSeparationVecLength(12.0f)
	, mIsMoving(false)
	, mIsDamage(false)
	, mMoveSpeed(1.0f)
	, mPeriodMoveCount(0)
	, mEnemyState(_State)
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
EnemyState EnemyObjectStateMove::Update(EnemyObject* _owner, const float _DeltaTime)
{
	// 座標
	mPosition = _owner->GetPosition();
	// 右方ベクトル
	Vector3 rightVec = _owner->GetRight();
	rightVec.z = 0.0f;

	// プレイヤーの座標
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// プレイヤーに向いたベクトル
	Vector3 dirPlayerVec = playerPos - mPosition;

	if (mEnemyState == EnemyState::eEnemyStateLeftMove)
	{
		rightVec *= -1.0f;
	}

	// 速度ベクトル
	mVelocity = mMoveSpeed * rightVec;
	mPosition += mVelocity;
	_owner->SetPosition(mPosition);
    
	++mPeriodMoveCount;

	if (mPeriodMoveCount >= MTransitionTimingNum)
	{
		if (dirPlayerVec.LengthSq() < 15000.0f)
		{
			// ランダム値
			int randNum = rand() % 100;

			if (randNum < 25)
			{
				return EnemyState::eEnemyStateWait;
			}
			else if (randNum >= 25 && randNum < 50)
			{
				return EnemyState::eEnemyStateLeftMove;

			}
			else if (randNum >= 50 && randNum < 75)
			{
				return EnemyState::eEnemyStateRightMove;
			}
			else
			{
				return EnemyState::eEnemyStateAttack;
			}
		}
		else if (dirPlayerVec.LengthSq() >= 15000.0f && dirPlayerVec.LengthSq() < MTransitionStateDistance)
		{
		    // ランダム値
			int randNum = rand() % 90;

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
	else if (mIsDamage)
	{
		return EnemyState::eEnemyStateDamage;
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
	mPeriodMoveCount = 0;
}

/// <summary>
/// エネミー同士の引き離し
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DirTargetEnemyVec"> 対象となるエネミーに向いたベクトル </param>
void EnemyObjectStateMove::Separation(EnemyObject* _owner, const Vector3& _DirTargetEnemyVec)
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
void EnemyObjectStateMove::OnColision(EnemyObject* _owner, const GameObject& _HitObject)
{
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eWeapon)
	{
		mIsDamage = true;
	}

	//押し戻し処理
	float dx1 = _HitObject.GetObjectAABB().m_min.x - _owner->GetObjectAABB().m_max.x;
	float dx2 = _HitObject.GetObjectAABB().m_max.x - _owner->GetObjectAABB().m_min.x;
	float dy1 = _HitObject.GetObjectAABB().m_min.y - _owner->GetObjectAABB().m_max.y;
	float dy2 = _HitObject.GetObjectAABB().m_max.y - _owner->GetObjectAABB().m_min.y;
	float dz1 = _HitObject.GetObjectAABB().m_min.z - _owner->GetObjectAABB().m_max.z;
	float dz2 = _HitObject.GetObjectAABB().m_max.z - _owner->GetObjectAABB().m_min.z;

	float dx = Math::Abs(dx1) < Math::Abs(dx2) ? dx1 : dx2;
	float dy = Math::Abs(dy1) < Math::Abs(dy2) ? dy1 : dy2;
	float dz = Math::Abs(dz1) < Math::Abs(dz2) ? dz1 : dz2;

	if (Math::Abs(dx) <= Math::Abs(dy) /*&& Math::Abs(dx) <= Math::Abs(dz)*/)
	{
		mPosition.x += dx;
	}
	else if (Math::Abs(dy) <= Math::Abs(dx) /*&& Math::Abs(dy) <= Math::Abs(dz)*/)
	{
		mPosition.y += dy;
	}
	//else
	////if (Math::Abs(dz) <= Math::Abs(dx) && Math::Abs(dz) <= Math::Abs(dy))
	//{
	//	mPosition.z += dz;
	//}

	_owner->SetPosition(mPosition);
}