#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
BossObjectStateTrack::BossObjectStateTrack(PlayerObject* _playerPtr)
	: MTimingTransitionOverheadAttack(240)
	, MTransitionStateDistance(30000.0f)
	, MVecShortenVelue(0.1f)
	, MSeparationVecLength(4.0f)
	, mIsDamage(false)
	, UntilTransitionOverheadAttackCount(0)
	, mMoveSpeed(5.0f)
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
BossState BossObjectStateTrack::Update(BossObject* _owner, const float _DeltaTime)
{
	// プレイヤーの座標
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// プレイヤーに向いたベクトル
	Vector3 dirPlayerVec = playerPos - mPosition;

	// ランダム値
	int randNum = rand() % 100;

	++UntilTransitionOverheadAttackCount;

	if (dirPlayerVec.LengthSq() < MTransitionStateDistance)
	{
		if (randNum < 20)
		{
			return BossState::eBossStateWait;
		}
		else if (randNum >= 20 && randNum < 40)
		{
			return BossState::eBossStateAreaAttack;
		}
		else if (randNum >= 40 && randNum < 60)
		{
			return BossState::eBossStateFrontAttack;
		}
		else if (randNum >= 60 && randNum < 80)
		{
			return BossState::eBossStateOverheadAttack;
		}
		else
		{
			return BossState::eBossStateTeleportation;
		}
	}
	else if(UntilTransitionOverheadAttackCount >= MTimingTransitionOverheadAttack)
	{
		if (randNum < 30)
		{
			return BossState::eBossStateOverheadAttack;
		}
		else if (randNum >= 30 && randNum < 60)
		{
			return BossState::eBossStateTeleportation;
		}
	}
	else if (mIsDamage)
	{
		return BossState::eBossStateDamage;
	}

	dirPlayerVec.Normalize();
	_owner->RotateToNewForward(dirPlayerVec);

	mVelocity = mMoveSpeed * dirPlayerVec;
	mPosition += mVelocity;
	// キャラの位置・スピード・変換行列の再計算の必要をセット
	_owner->SetPosition(mPosition);

	return BossState::eBossStateTrack;
}

/// <summary>
/// ボスの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> ボス(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void BossObjectStateTrack::Enter(BossObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(BossState::eBossStateTrack));

	mIsDamage = false;
	UntilTransitionOverheadAttackCount = 0;

	// 座標
	mPosition = _owner->GetPosition();
}

/// <summary>
/// ボス同士の引き離し
/// </summary>
/// <param name="_owner"> ボス(親)のポインタ </param>
/// <param name="_DirTargetEnemyVec"> 対象となるエネミーに向いたベクトル </param>
void BossObjectStateTrack::Separation(BossObject* _owner, const Vector3& _DirTargetEnemyVec)
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
void BossObjectStateTrack::OnCollision(BossObject* _owner, const GameObject& _HitObject)
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