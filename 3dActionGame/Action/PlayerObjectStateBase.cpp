#include "PlayerObjectStateBase.h"

PlayerObjectStateBase::PlayerObjectStateBase()
	: mNextComboFlag(false)
	, mIdleFlag(false)
	, mRunStartFlag(false)
	, mRunFlag(false)
	, mSprintFlag(false)
	, mAttackFlag(false)
	, mSwordDeliveryFlag(false)
	, mDrawnSwordFlag(false)
	, mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
	, mCharaSpeed(0.0f)
	, mDirVec(Vector3::Zero)
	, mForwardVec(Vector3::Zero)
	, mRightVec(Vector3::Zero)
	, mCharaForwardVec(Vector3::Zero)
{

}