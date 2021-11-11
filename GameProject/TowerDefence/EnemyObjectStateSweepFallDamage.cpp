#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
EnemyObjectStateSweepFallDamage::EnemyObjectStateSweepFallDamage(PlayerObject* _playerPtr)
	: mHitTagList{ Tag::eDashAttackEffect, Tag::eFirstAttackEffect, Tag::eSecondAttackEffect, Tag::eThirdAttackEffect }
	, MDamageValuePlayerFirstAttack(25)
	, MVecShortenVelue(0.1f)
	, MSeparationVecLength(4.0f)
	, MDamageInitSpeed(100.0f)
	, MGravity(4.0f)
	, mIsDamage(false)
	, mHitPoint(0)
	, mDamageValue(0)
	, mHitTagListSize(sizeof(mHitTagList) / sizeof(int))
	, mDamageSpeed(0.0f)
	, mPosition(Vector3::Zero)
	, mNowStateInitPos(Vector3::Zero)
	, mVelocity(Vector3::Zero)
	, mDirPlayerVec(Vector3::Zero)
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
EnemyState EnemyObjectStateSweepFallDamage::Update(EnemyObject* _owner, const float _DeltaTime)
{
	if (mHitPoint <= 0)
	{
		return EnemyState::eEnemyStateSweepFallDeath;
	}

 	if (mIsDamage)
	{
		switch (mHitTag)
		{
		case Tag::eDashAttackEffect:

			return EnemyState::eEnemyStateImpactDamage;

		case Tag::eFirstAttackEffect:

			return EnemyState::eEnemyStateImpactDamage;

		case Tag::eThirdAttackEffect:

			return EnemyState::eEnemyStateFlyingBackDamage;
		}
	}

	// 速度
	Vector3 velocity = mDamageSpeed * Vector3::UnitZ;
	mDamageSpeed -= MGravity;

	mPosition += velocity * _DeltaTime;

	if (mPosition.z <= mNowStateInitPos.z)
	{
		mPosition.z = mNowStateInitPos.z;
	}

	_owner->SetPosition(mPosition);

	// アニメーションが終了したら待機状態へ
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		return EnemyState::eEnemyStateStandUp;
	}

	return EnemyState::eEnemyStateSweepFallDamage;
}

/// <summary>
/// エネミー同士の引き離し
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DirTargetEnemyVec"> 対象となるエネミーに向いたベクトル </param>
void EnemyObjectStateSweepFallDamage::Separation(EnemyObject* _owner, const Vector3& _DirTargetEnemyVec)
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
/// エネミーの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void EnemyObjectStateSweepFallDamage::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	mIsDamage = false;

	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateSweepFallDamage));

	// 座標
	mPosition = _owner->GetPosition();
	// このステートに入った時の座標
	mNowStateInitPos = mPosition;
	// プレイヤーの座標
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// プレイヤーに向いたベクトル
	mDirPlayerVec = playerPos - mPosition;
	mDirPlayerVec.Normalize();

	mDamageSpeed = MDamageInitSpeed;

	// ダメージ値
	int damageValue = _owner->GetDamageValue();
	// 体力
	mHitPoint = _owner->GetHitPoint() - damageValue;

	_owner->RotateToNewForward(mDirPlayerVec);
	_owner->SetHitPoint(mHitPoint);
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void EnemyObjectStateSweepFallDamage::OnCollision(EnemyObject* _owner, const GameObject& _HitObject)
{
	mEnemyPtr = _owner;

	// オブジェクトのタグ
	mHitTag = _HitObject.GetTag();

	for (int i = 0; i < mHitTagListSize; i++)
	{
		// 攻撃を受けた時の処理
		if (ReceivedAttack(mHitTagList[i], MDamageValuePlayerFirstAttack))
		{
			mPosition.z = mNowStateInitPos.z;
			_owner->SetPosition(mPosition);
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
bool EnemyObjectStateSweepFallDamage::ReceivedAttack(const Tag& _hitTag, const int& _DamageValuePlayerAttack)
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