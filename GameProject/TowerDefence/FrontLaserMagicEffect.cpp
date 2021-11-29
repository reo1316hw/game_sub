#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>	
/// <param name="_bossPtr"> ボスのポインタ </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
FrontLaserMagicEffect::FrontLaserMagicEffect(BossObject* _bossPtr, const Vector3& _Scale, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MBoxEnableTiming(0.5f)
	, MHeightCorrection(Vector3(0.0f, 0.0f, 50.0f))
	, mIsPlayEffect(false)
	, mElapseTime(0.0f)
	, mBossPtr(_bossPtr)
	, mEffectComponentPtr(nullptr)
{
	// エフェクト生成
	mEffectComponentPtr = new EffectComponent(this, _Scale, u"Assets/Effect/FrontLaserMagic.efk", true, true);
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void FrontLaserMagicEffect::UpdateGameObject(float _deltaTime)
{
	// 現在のステート
	BossState nowState = mBossPtr->GetNowState();

	if (nowState != BossState::eBossStateFrontAttack)
	{
		mEffectComponentPtr->StopEffect();
		mElapseTime = 0.0f;
		mIsPlayEffect = false;
		return;
	}

	mElapseTime += _deltaTime;

	if (mElapseTime >= MBoxEnableTiming)
	{
		mPosition = mBossPtr->GetPosition() + MHeightCorrection;
		SetPosition(mPosition);
		SetRotation(mBossPtr->GetRotation());

		if (!mIsPlayEffect)
		{
			// エフェクトを再生
			mEffectComponentPtr->PlayEffect();
		}

		mIsPlayEffect = true;
	}
}