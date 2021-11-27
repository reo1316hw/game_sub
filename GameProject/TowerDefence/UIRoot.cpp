#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
/// <param name="_bossPtr"> ボスのポインタ </param>
/// <param name="_enemyObjectManagerPtr"> エネミーを管理するクラスのポインタ </param>
/// <param name="_enemyActiveBoxPtr"> エネミーを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
/// <param name="_bossActiveBoxPtr"> ボスを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
UIRoot::UIRoot(const Tag& _ObjectTag, PlayerObject* _playerPtr, BossObject* _bossPtr, 
	EnemyObjectManager* _enemyObjectManagerPtr, DeadObjectActiveBox* _enemyActiveBoxPtr,
	DeadObjectActiveBox* _bossActiveBoxPtr)
	: GameObject(_ObjectTag)
	, MPlayerHitPointScale(Vector3(1.0f, 0.4f, 1.0f))
	, MBossHitPointScale(Vector3(1.0f, 0.3f, 1.0f))
	, MDeadEnemyCountScale(Vector3(1.0f, 0.3f, 1.0f))
	, MDeadEnemyCountTextScale(Vector3(1.0f, 0.5f, 1.0f))
	, MDefeatEnemyNumberTextScale(Vector3(1.0f, 0.5f, 1.0f))
	, MOperationExplanationScale(Vector3(1.3f, 0.8f, 1.0f))
	, MPlayerHitPointPosition(Vector3(-800.0f, -400.0f, 0.0f))
	, MBossHitPointGaugePosition(Vector3(357.0f, 400.0f, 0.0f))
	, MBossHitPointFramePosition(Vector3(350.0f, 400.0f, 0.0f))
	, MDeadEnemyCountGaugePosition(Vector3(-793.0f, 400.0f, 0.0f))
	, MDeadEnemyCountFramePosition(Vector3(-800.0f, 400.0f, 0.0f))
	, MDeadEnemyCountTextPosition(Vector3(-250.0f, 400.0f, 0.0f))
	, MDefeatEnemyNumberTextPosition(Vector3(-220.0f, 400.0f, 0.0f))
	, MOperationExplanationtPosition(Vector3(1030.0f, -270.0f, 0.0f))
{
	// プレイヤーのhpゲージを生成
	new SpriteGauge(_playerPtr, MPlayerHitPointPosition, "Assets/Texture/PlayerHpGauge.png", Tag::eOther, State::eActive, MPlayerHitPointScale);
	// プレイヤーのhpの枠を生成
	new SpriteFrame(MPlayerHitPointPosition, "Assets/Texture/PlayerHpFrame.png", Tag::eOther, State::eActive, MPlayerHitPointScale);
	// ボスのhpゲージを生成
	SpriteGauge* bossHitPointGaugePtr = new SpriteGauge(_bossPtr, MBossHitPointGaugePosition, "Assets/Texture/EnemyHpGauge.png", Tag::eOther, State::eActive, MBossHitPointScale);
	// ボスのhpの枠を生成
	SpriteFrame* bossHitPointFramePtr = new SpriteFrame(MBossHitPointFramePosition, "Assets/Texture/SpriteFrame.png", Tag::eOther, State::eActive, MBossHitPointScale);
	// 倒したエネミーのカウントゲージを生成
	SpriteGauge* deadEnemyCountGaugePtr = new SpriteGauge(_enemyObjectManagerPtr, MDeadEnemyCountGaugePosition, "Assets/Texture/DeadEnemyCountGauge.png", Tag::eOther, State::eActive, _enemyObjectManagerPtr, MDeadEnemyCountScale, true);
	// 倒したエネミーのカウントフレームを生成
	SpriteFrame* deadEnemyCountFramePtr = new SpriteFrame(MDeadEnemyCountFramePosition, "Assets/Texture/SpriteFrame.png", Tag::eOther, State::eActive, _enemyObjectManagerPtr, MDeadEnemyCountScale);

	// 倒したエネミーのカウントUIを生成
	DeadEnemyCountText* deadEnemyCountTextPtr = new DeadEnemyCountText(MDeadEnemyCountTextPosition, Tag::eOther, _enemyObjectManagerPtr, MDeadEnemyCountTextScale);
	// チュートリアルエリアの倒すエネミーの数のUIを生成
	DefeatEnemyNumberText* defeatTutorialEnemyNumberTextPtr = new DefeatEnemyNumberText(MDefeatEnemyNumberTextPosition, Tag::eOther, State::eActive, 101, _enemyObjectManagerPtr, MDefeatEnemyNumberTextScale);
	// 無限にエネミーが湧いてくるエリアの倒すエネミーの数のUIを生成
	DefeatEnemyNumberText* defeatInfinitelyEnemyNumberTextPtr = new DefeatEnemyNumberText(MDefeatEnemyNumberTextPosition, Tag::eOther, State::eDead, 102, _enemyObjectManagerPtr, MDefeatEnemyNumberTextScale);

	// 操作説明UIを生成
	OperationExplanation* operationExplanationPtr = new OperationExplanation(MOperationExplanationtPosition, "Assets/Texture/OperationExplanation.png", Tag::eOther, _playerPtr, MOperationExplanationScale);

	// ボスのhpゲージを有効にするコンポーネントを生成
	new DeadObjectEnable(this, _bossActiveBoxPtr, bossHitPointGaugePtr);
	// ボスのhpの枠を有効にするコンポーネントを生成
	new DeadObjectEnable(this, _bossActiveBoxPtr, bossHitPointFramePtr);
	// 倒したエネミーのカウントゲージを有効にするコンポーネントを生成
	new DeadObjectEnable(this, _enemyActiveBoxPtr, deadEnemyCountGaugePtr);
	// 倒したエネミーのカウントフレームを有効にするコンポーネントを生成
	new DeadObjectEnable(this, _enemyActiveBoxPtr, deadEnemyCountFramePtr);
	// 倒したエネミーのカウントUIを有効にするコンポーネントを生成
	new DeadObjectEnable(this, _enemyActiveBoxPtr, deadEnemyCountTextPtr);
	// 無限にエネミーが湧いてくるエリアの倒すエネミーの数のUIを有効にするコンポーネントを生成
	new DeadObjectEnable(this, _enemyActiveBoxPtr, defeatInfinitelyEnemyNumberTextPtr);
	// 操作説明UIを有効にするコンポーネントを生成
	new DeadObjectEnable(this, _playerPtr, operationExplanationPtr);
}