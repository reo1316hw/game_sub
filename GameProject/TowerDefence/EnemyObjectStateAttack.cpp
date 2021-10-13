#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
EnemyObjectStateAttack::EnemyObjectStateAttack()
	: MAttackSpeed(150.0f)
	, MVecShortenVelue(0.1f)
	, MPlayRate(1.5f)
	, MSeparationVecLength(4.0f)
	, mIsDamage(false)
	, mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
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
	// 座標
	mPosition = _owner->GetPosition();
	// 前方ベクトル
	Vector3 forward = _owner->GetForward();
	// 開始速度
	float startSpeed = MAttackSpeed * _DeltaTime;
	// 終了速度
	float endSpeed = -MAttackSpeed * _DeltaTime;

	// 攻撃踏み込み移動のためのアニメーション再生時間の経過割合を計算
	mElapseTime += _DeltaTime;
	// 経過割合をもとに移動処理
	mPosition += Quintic::EaseIn(mElapseTime, startSpeed, endSpeed, mTotalAnimTime) * forward;

	_owner->SetPosition(mPosition);

	// アニメーションが終了したら移動状態へ
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		// ランダム値
		int randNum = rand() % 90;
		
		if (randNum < 30)
		{
			return EnemyState::eEnemyStateWait;
		}
		else if(randNum >= 30 && randNum < 60)
		{
			return EnemyState::eEnemyStateLeftMove;
		}
		else
		{
			return EnemyState::eEnemyStateRightMove;
		}
	}
	else if (mIsDamage)
	{
		return EnemyState::eEnemyStateDamage;
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

	mIsDamage = false;
	// アニメーション再生時間取得
	mTotalAnimTime = _owner->GetAnimPtr(EnemyState::eEnemyStateAttack)->GetDuration() - 0.5f;
	mElapseTime = 0.0f;
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
void EnemyObjectStateAttack::OnColision(EnemyObject* _owner, const GameObject& _HitObject)
{
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eWeapon)
	{
		mIsDamage = true;
	}

	if (tag == Tag::ePlayer)
	{
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
}