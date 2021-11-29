#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>	
/// <param name="_bossPtr"> ボスのポインタ </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
TeleportationEffect::TeleportationEffect(BossObject* _bossPtr, const Vector3& _Scale, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MPlayRate(5.0f)
	, MHeightCorrection(Vector3(0.0f, 0.0f, 50.0f))
	, mIsPlayEffect(false)
	, mNowState(_bossPtr->GetNowState())
	, mBossPtr(_bossPtr)
	, mEffectComponentPtr(nullptr)
{
	// エフェクト生成
	mEffectComponentPtr = new EffectComponent(this, _Scale, u"Assets/Effect/Telepotation.efk", true, true);
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void TeleportationEffect::UpdateGameObject(float _deltaTime)
{
	// 前のステート
	BossState preState = mNowState;

	mNowState = mBossPtr->GetNowState();

	if (mNowState == preState)
	{
		mIsPlayEffect = false;
		return;
	}

	if (preState == BossState::eBossStateTeleportation)
	{
		mPosition = mBossPtr->GetPosition() + MHeightCorrection;
		SetPosition(mPosition);
		SetRotation(mBossPtr->GetRotation());

		// エフェクトを再生
		mEffectComponentPtr->PlayEffect(MPlayRate);
		return;
	}

	if (mNowState != BossState::eBossStateTeleportation)
	{
		mIsPlayEffect = false;
		return;
	}

	mPosition = mBossPtr->GetPosition() + MHeightCorrection;
	SetPosition(mPosition);
	SetRotation(mBossPtr->GetRotation());

	if (!mIsPlayEffect)
	{
		// エフェクトを再生
		mEffectComponentPtr->PlayEffect(MPlayRate);
	}

	mIsPlayEffect = true;
}