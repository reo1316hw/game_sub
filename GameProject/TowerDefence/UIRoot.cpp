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
	, MPlayerHitPointScale(Vector2(1.0f, 0.5f))
	, MBossHitPointScale(Vector2(1.0f, 0.5f))
{
	// プレイヤーのhpゲージを生成
	new PlayerHitPointGauge(MPlayerHitPointPosition, "Assets/Texture/PlayerHpGauge.png", Tag::eOther, _playerPtr, MPlayerHitPointScale);
	// プレイヤーのhpの枠を生成
	new PlayerHitPointFrame(MPlayerHitPointPosition, "Assets/Texture/PlayerHpFrame.png", Tag::eOther, MPlayerHitPointScale);
	// ボスのhpゲージを生成
	BossHitPointGauge* bossHitPointGaugePtr = new BossHitPointGauge(MBossHitPointPosition, "Assets/Texture/EnemyHpGauge.png", Tag::eOther, _bossPtr, MBossHitPointScale);
	// ボスのhpの枠を生成
	BossHitPointFrame* bossHitPointFramePtr = new BossHitPointFrame(MBossHitPointPosition, "Assets/Texture/EnemyHpFrame.png", Tag::eOther, MBossHitPointScale);

	// ボスの体力UIのON/OFFを行うコンポーネントを生成
	new BossHitPointUISwitch(this, _bossActiveBoxPtr, bossHitPointGaugePtr, bossHitPointFramePtr);

	// 
	new DeadEnemyCountText(Vector3::Zero, Tag::eOther, Vector2(5.0f, 1.0f));
}