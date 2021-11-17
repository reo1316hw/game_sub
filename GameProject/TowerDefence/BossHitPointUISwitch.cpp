#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
/// <param name="_bossActiveBoxPtr"> ボスを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
/// <param name="_bossHitPointGaugePtr"> ボスのhpゲージのポインタ </param>
/// <param name="_bossHitPointFramePtr"> ボスのhpの枠のポインタ </param>
BossHitPointUISwitch::BossHitPointUISwitch(GameObject* _owner, BossActiveBox* _bossActiveBoxPtr,
	BossHitPointGauge* _bossHitPointGaugePtr, BossHitPointFrame* _bossHitPointFramePtr)
	: Component(_owner)
	, mBossActiveBoxPtr(_bossActiveBoxPtr)
	, mBossHitPointGaugePtr(_bossHitPointGaugePtr)
	, mBossHitPointFramePtr(_bossHitPointFramePtr)
{
}

/// <summary>
/// フレーム毎の処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 < /param>
void BossHitPointUISwitch::Update(float _deltaTime)
{
	if (!mBossActiveBoxPtr->GetIsHitPlayer() || mBossHitPointGaugePtr->GetState() == eActive
		&& mBossHitPointFramePtr->GetState() == eActive)
	{
		return;
	}

	mBossHitPointGaugePtr->SetState(eActive);
	mBossHitPointFramePtr->SetState(eActive);
}