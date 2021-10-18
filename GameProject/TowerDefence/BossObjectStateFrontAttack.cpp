#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
BossObjectStateFrontAttack::BossObjectStateFrontAttack(PlayerObject* _playerPtr)
	: MTimingFixFacing(30)
	, MTransitionStateDistance(30000.0f)
	, MVecShortenVelue(0.1f)
	, MSeparationVecLength(8.0f)
	, mIsDamage(false)
	, mFacingFixUntilTime(0)
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
BossState BossObjectStateFrontAttack::Update(BossObject* _owner, const float _DeltaTime)
{
	_owner->SetPosition(mPosition);

	// プレイヤーの座標
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// プレイヤーに向いたベクトルsd
	Vector3 dirPlayerVec = playerPos - mPosition;

	++mFacingFixUntilTime;

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

	if (mFacingFixUntilTime < MTimingFixFacing)
	{
		dirPlayerVec.Normalize();
		_owner->RotateToNewForward(dirPlayerVec);
	}

	return BossState::eBossStateFrontAttack;
}

/// <summary>
/// ボスの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> ボス(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void BossObjectStateFrontAttack::Enter(BossObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(BossState::eBossStateFrontAttack));

	mIsDamage = false;
	mFacingFixUntilTime = 0;

	// 座標
	mPosition = _owner->GetPosition();
}

/// <summary>
/// ボスとエネミーの引き離し
/// </summary>
/// <param name="_owner"> ボス(親)のポインタ </param>
/// <param name="_DirTargetEnemyVec"> 対象となるエネミーに向いたベクトル </param>
void BossObjectStateFrontAttack::Separation(BossObject* _owner, const Vector3& _DirTargetEnemyVec)
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
void BossObjectStateFrontAttack::OnCollision(BossObject* _owner, const GameObject& _HitObject)
{
	// 座標
	mPosition = _owner->GetPosition();

	// オブジェクトのタグ
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eWeapon)
	{
		mIsDamage = true;
	}
}