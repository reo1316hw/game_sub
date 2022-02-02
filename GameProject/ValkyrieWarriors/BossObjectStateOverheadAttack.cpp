#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
BossObjectStateOverheadAttack::BossObjectStateOverheadAttack(PlayerObject* _playerPtr)
	: mHitTagList{ Tag::eDashAttackEffect, Tag::eFirstAttackEffect, Tag::eSecondAttackEffect, Tag::eThirdAttackEffect }
	, mDamageValueList{ 10, 5, 15, 25 }
	, MTransitionStateDistance(30000.0f)
	, MVecShortenVelue(0.1f)
	, MSeparationVecLength(8.0f)
	, mIsDamage(false)
	, mDashAttackIsChangeHitPoint(false)
	, mFirstAttackIsChangeHitPoint(false)
	, mDamageValue(0)
	, mHitTagListSize(sizeof(mHitTagList) / sizeof(int))
	, mHitPoint(0)
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
	, mHitTag(Tag::eOther)
	, mBossPtr(nullptr)
	, mPlayerPtr(_playerPtr)
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="_owner"> ボス(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
/// <returns> ボスの状態 </returns>
BossState BossObjectStateOverheadAttack::Update(BossObject* _owner, const float _DeltaTime)
{
	if (mPlayerPtr->GetNowState() != PlayerState::ePlayerStateDashAttack)
	{
		mDashAttackIsChangeHitPoint = false;
	}

	if (mPlayerPtr->GetNowState() != PlayerState::ePlayerStateFirstAttack)
	{
		mFirstAttackIsChangeHitPoint = false;
	}

	if (mIsDamage)
	{
		switch (mHitTag)
		{
		case Tag::eDashAttackEffect:

			// hpが変更されたらダメージを負う処理を現在のステートに次回入るまで行わないようにする
			if (mDashAttackIsChangeHitPoint)
			{
				break;
			}

			// ダメージを負う処理
			SufferDamage(_owner);

			mDashAttackIsChangeHitPoint = true;

			break;

		case Tag::eFirstAttackEffect:

			// hpが変更されたらダメージを負う処理を現在のステートに次回入るまで行わないようにする
			if (mFirstAttackIsChangeHitPoint)
			{
				break;
			}

			// ダメージを負う処理
			SufferDamage(_owner);

			mFirstAttackIsChangeHitPoint = true;

			break;

		case Tag::eSecondAttackEffect:

			return BossState::eBossStateSweepFallDamage;

		case Tag::eThirdAttackEffect:

			return BossState::eBossStateFlyingBackDamage;
		}
	}

	if (mHitPoint <= 0)
	{
		return BossState::eBossStateDeath;
	}

	mIsDamage = false;

	_owner->SetPosition(mPosition);

	// プレイヤーの座標
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// プレイヤーに向いたベクトルsd
	Vector3 dirPlayerVec = playerPos - mPosition;

	// アニメーションが終了したら移動状態へ
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		if (dirPlayerVec.LengthSq() < MTransitionStateDistance)
		{
			// ランダム値
			int randNum = rand() % 100;

			if (randNum < 50)
			{
				return BossState::eBossStateWait;
			}
			else
			{
				return BossState::eBossStateTeleportation;
			}
		}

		return BossState::eBossStateTrack;
	}

	return BossState::eBossStateOverheadAttack;
}

/// <summary>
/// ボスの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> ボス(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void BossObjectStateOverheadAttack::Enter(BossObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(BossState::eBossStateOverheadAttack));

	mIsDamage = false;

	// 体力
	mHitPoint = _owner->GetHitPoint();
	// 座標
	mPosition = _owner->GetPosition();
}

/// <summary>
/// ボスとエネミーの引き離し
/// </summary>
/// <param name="_owner"> ボス(親)のポインタ </param>
/// <param name="_DirTargetEnemyVec"> 対象となるエネミーに向いたベクトル </param>
void BossObjectStateOverheadAttack::Separation(BossObject* _owner, const Vector3& _DirTargetEnemyVec)
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
void BossObjectStateOverheadAttack::OnCollision(BossObject* _owner, const GameObject& _HitObject)
{
	mBossPtr = _owner;
	// 座標
	mPosition = mBossPtr->GetPosition();

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
bool BossObjectStateOverheadAttack::ReceivedAttack(const Tag& _hitTag, const int& _DamageValuePlayerAttack)
{
	if (mHitTag == _hitTag)
	{
		mDamageValue = _DamageValuePlayerAttack;
		mIsDamage = true;

		mBossPtr->SetDamageValue(mDamageValue);
		return true;
	}

	return false;
}

/// <summary>
/// ダメージを負う処理
/// </summary>
/// <param name="_owner"> ボス(親)のポインタ </param>
void BossObjectStateOverheadAttack::SufferDamage(BossObject* _owner)
{
	// ダメージ値
	int damageValue = _owner->GetDamageValue();
	// 体力
	mHitPoint = _owner->GetHitPoint() - damageValue;

	// オブジェクトのスケールサイズを求めるための左辺の値を設定
	_owner->SetScaleLeftSideValue(mHitPoint);
	_owner->SetHitPoint(mHitPoint);
}