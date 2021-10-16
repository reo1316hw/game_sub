#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_enemyAttackPtr"> エネミーの攻撃判定オブジェクトのポインタ </param>
EnemyObjectStateAttack::EnemyObjectStateAttack(EnemyAttackDecisionObject* _enemyAttackPtr)
	: MBoxEnableTiming(20)
	, MAttackSpeed(150.0f)
	, MPlayRate(1.5f)
	, MVecShortenVelue(0.1f)
	, MSeparationVecLength(4.0f)
	, mIsDamage(false)
	, mHitUntilCount(0)
	, mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
	, mForwardVec(Vector3::Zero)
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

	++mHitUntilCount;

	if (mHitUntilCount == MBoxEnableTiming)
	{
		// 武器の当たり判定を行うようにする
		mOwnerBoxCollider->SetCollisionState(CollisionState::eEnableCollision);
	}

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
	mHitUntilCount = 0;

	// 座標
	mPosition = _owner->GetPosition();
	// 前方ベクトル
	mForwardVec = _owner->GetForward();

	_owner->RotateToNewForward(mForwardVec);
}

/// <summary>
/// エネミーの状態が変更して、最後に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void EnemyObjectStateAttack::Exit(EnemyObject* _owner, const float _DeltaTime)
{
	// 武器の当たり判定を行わないようにする
	mOwnerBoxCollider->SetCollisionState(CollisionState::eDisableCollision);
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
	// オブジェクトのタグ
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eWeapon)
	{
		mIsDamage = true;
	}
}