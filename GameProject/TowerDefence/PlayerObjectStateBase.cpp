#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerObjectStateBase::PlayerObjectStateBase()
	: mIsNextCombo(false)
	, mIsIdle(false)
	, mIsRun(false)
	, mIsSprint(false)
	, mIsAttack(false)
	, mIsHit(false)
	, mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
	, mCharaSpeed(0.0f)
	, mDirVec(Vector3::Zero)
	, mForwardVec(Vector3::Zero)
	, mRightVec(Vector3::Zero)
	, mCharaForwardVec(Vector3::Zero)
	, mAttackBoneIndex(0)
	, mAttackMeshComponent(nullptr)
{

}