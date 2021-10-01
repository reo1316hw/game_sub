#include "pch.h"

PlayerObjectStateBase::PlayerObjectStateBase()
	: mNextComboFlag(false)
	, mIdleFlag(false)
	, mSprintStartFlag(false)
	, mRunFlag(false)
	, mSprintFlag(false)
	, mAttackFlag(false)
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