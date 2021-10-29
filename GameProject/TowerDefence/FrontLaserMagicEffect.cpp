#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>	
/// <param name="_bossPtr"> ボスのポインタ </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
FrontLaserMagicEffect::FrontLaserMagicEffect(BossObject* _bossPtr, const Vector3& _Scale, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MHeightCorrection(Vector3(0.0f, 0.0f, 50.0f))
	, mNowState(_bossPtr->GetNowState())
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
	mPosition = mBossPtr->GetPosition() + MHeightCorrection;
	SetPosition(mPosition);
	SetRotation(mBossPtr->GetRotation());

	// 前のステート
	BossState preState = mNowState;
	
	mNowState = mBossPtr->GetNowState();
	
	if (mNowState == preState)
	{
		return;
	}

	if (mNowState != BossState::eBossStateFrontAttack)
	{
		return;
	}

	// 再生済みじゃなかったらエフェクトを再生する
	if (mEffectComponentPtr->IsPlayedEffect())
	{
		// エフェクトを再生
		mEffectComponentPtr->PlayEffect();
	}
}