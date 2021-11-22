#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
BossObjectStateTeleportation::BossObjectStateTeleportation(PlayerObject* _playerPtr)
	: MTimingTeleportationEnding(120)
	, MTransitionStateDistance(30000.0f)
	, mIsDamage(false)
	, mUntilTeleportationEndingCount(0)
	, mTeleportationVec(Vector3::Zero)
	, mPosition(Vector3::Zero)
	, mPlayerPtr(_playerPtr)
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="_owner"> ボス(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
/// <returns> ボスの状態 </returns>
BossState BossObjectStateTeleportation::Update(BossObject* _owner, const float _DeltaTime)
{
	// プレイヤーの座標
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// プレイヤーに向いたベクトルsd
	Vector3 dirPlayerVec = playerPos - mPosition;

	mPosition = playerPos + mTeleportationVec * 100.0f;

	++mUntilTeleportationEndingCount;

	_owner->SetPosition(mPosition);

	if (mUntilTeleportationEndingCount >= MTimingTeleportationEnding)
	{
		if (dirPlayerVec.LengthSq() < MTransitionStateDistance)
		{
			// ランダム値
			int randNum = rand() % 100;

			if (randNum < 30)
			{
				return BossState::eBossStateAreaAttack;
			}
			else if (randNum >= 30 && randNum < 60)
			{
				return BossState::eBossStateFrontAttack;
			}
			else if (randNum >= 60 && randNum < 90)
			{
				return BossState::eBossStateOverheadAttack;
			}
			else
			{
				return BossState::eBossStateWait;
			}
		}

		return BossState::eBossStateTrack;
	}
	
	return BossState::eBossStateTeleportation;
}

/// <summary>
/// ボスの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> ボス(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void BossObjectStateTeleportation::Enter(BossObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(BossState::eBossStateTeleportation));

	mIsDamage = false;
	mUntilTeleportationEndingCount = 0;

	// 座標
	mPosition = _owner->GetPosition();

	int randnum = rand() % 4;

	switch (randnum)
	{
	case 0:

		mTeleportationVec = Vector3::UnitX + Vector3::UnitY;

		break;
	case 1:

		mTeleportationVec = Vector3::NegUnitX + Vector3::UnitY;

		break;
	case 2:

		mTeleportationVec = Vector3::NegUnitX + Vector3::NegUnitY;

		break;
	case 3:

		mTeleportationVec = Vector3::UnitX + Vector3::NegUnitY;

		break;
	}

	// プレイヤーの回転値
	Quaternion playerRotation = mPlayerPtr->GetRotation();
	// テレポートする向き
	mTeleportationVec = Vector3::Transform(mTeleportationVec, playerRotation);

	// 透明にする
	_owner->GetSkeletalMeshComponentPtr()->SetVisible(false);
}

/// <summary>
/// ボスの状態が変更して、最後に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> ボス(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void BossObjectStateTeleportation::Exit(BossObject* _owner, const float _DeltaTime)
{
	// 不透明にする
	_owner->GetSkeletalMeshComponentPtr()->SetVisible(true);
}