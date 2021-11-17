#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
/// <param name="_bossPtr"> ボスのポインタ </param>
/// <param name="_bossActiveBoxPtr"> ボスを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
UIRoot::UIRoot(const Tag& _ObjectTag, PlayerObject* _playerPtr,
	BossObject* _bossPtr, BossActiveBox* _bossActiveBoxPtr)
	: GameObject(_ObjectTag)
	, MPlayerHitPointPosition(Vector3(-800.0f, -400.0f, 0.0f))
	, MBossHitPointPosition(Vector3(400.0f, 400.0f, 0.0f))
	, mBossActiveBoxPtr(_bossActiveBoxPtr)
	, mBossHitPointGaugePtr(nullptr)
	, mBossHitPointFramePtr(nullptr)
{
	// プレイヤーのhpゲージを生成
	new PlayerHitPointGauge(MPlayerHitPointPosition, "Assets/Texture/PlayerHpGauge.png", Tag::eOther, _playerPtr);
	// プレイヤーのhpの枠を生成
	new PlayerHitPointFrame(MPlayerHitPointPosition, "Assets/Texture/PlayerHpFrame.png", Tag::eOther);
	// ボスのhpゲージを生成
	mBossHitPointGaugePtr = new BossHitPointGauge(MBossHitPointPosition, "Assets/Texture/EnemyHpGauge.png", Tag::eOther, _bossPtr);
	// ボスのhpの枠を生成
	mBossHitPointFramePtr = new BossHitPointFrame(MBossHitPointPosition, "Assets/Texture/EnemyHpFrame.png", Tag::eOther);
}

/// <summary>
/// ゲームオブジェクトのアップデート
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void UIRoot::UpdateGameObject(float _deltaTime)
{
	if (!mBossActiveBoxPtr->GetIsHitPlayer() || mBossHitPointGaugePtr->GetState() == eActive 
		&& mBossHitPointFramePtr->GetState() == eActive)
	{
		return;
	}

	mBossHitPointGaugePtr->SetState(eActive);
	mBossHitPointFramePtr->SetState(eActive);
}