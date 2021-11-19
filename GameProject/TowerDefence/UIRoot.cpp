#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
/// <param name="_bossPtr"> ボスのポインタ </param>
/// <param name="_enemyActiveBoxPtr"> エネミーを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
/// <param name="_bossActiveBoxPtr"> ボスを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
/// <param name="_enemysControlerPtr"> エネミーたちを制御するクラスのポインタ </param>
UIRoot::UIRoot(const Tag& _ObjectTag, PlayerObject* _playerPtr, BossObject* _bossPtr, DeadObjectActiveBox* _enemyActiveBoxPtr, 
	DeadObjectActiveBox* _bossActiveBoxPtr, EnemysControler* _enemysControlerPtr)
	: GameObject(_ObjectTag)
	, MTutorialDefeatEnemyNum(10)
	, MInfinitelyDefeatEnemyNum(100)
	, MPlayerHitPointScale(Vector3(1.0f, 0.5f, 1.0f))
	, MBossHitPointScale(Vector3(1.0f, 0.5f, 1.0f))
	, MDeadEnemyCountTextScale(Vector3(1.0f, 0.5f, 1.0f))
	, MDefeatEnemyNumberTextScale(Vector3(1.0f, 0.5f, 1.0f))
	, MPlayerHitPointPosition(Vector3(-800.0f, -400.0f, 0.0f))
	, MBossHitPointPosition(Vector3(400.0f, 400.0f, 0.0f))
	, MDeadEnemyCountTextPosition(Vector3(-600.0f, 400.0f, 0.0f))
	, MDefeatEnemyNumberTextPosition(Vector3(-570.0f, 400.0f, 0.0f))
{
	// プレイヤーのhpゲージを生成
	new PlayerHitPointGauge(MPlayerHitPointPosition, "Assets/Texture/PlayerHpGauge.png", Tag::eOther, _playerPtr, MPlayerHitPointScale);
	// プレイヤーのhpの枠を生成
	new PlayerHitPointFrame(MPlayerHitPointPosition, "Assets/Texture/PlayerHpFrame.png", Tag::eOther, MPlayerHitPointScale);
	// ボスのhpゲージを生成
	BossHitPointGauge* bossHitPointGaugePtr = new BossHitPointGauge(MBossHitPointPosition, "Assets/Texture/EnemyHpGauge.png", Tag::eOther, _bossPtr, MBossHitPointScale);
	// ボスのhpの枠を生成
	BossHitPointFrame* bossHitPointFramePtr = new BossHitPointFrame(MBossHitPointPosition, "Assets/Texture/EnemyHpFrame.png", Tag::eOther, MBossHitPointScale);

	// チュートリアルエリア倒したエネミーのカウントUIを生成
	DeadEnemyCountText* deadTutorialEnemyCountTextPtr = new DeadEnemyCountText(MDeadEnemyCountTextPosition, Tag::eOther, State::eActive, MTutorialDefeatEnemyNum, _enemysControlerPtr, MDeadEnemyCountTextScale);
	// 倒したエネミーのカウントUIを生成
	DeadEnemyCountText* deadInfinitelyEnemyCountTextPtr = new DeadEnemyCountText(MDeadEnemyCountTextPosition, Tag::eOther, State::eDead, MInfinitelyDefeatEnemyNum, _enemysControlerPtr, MDeadEnemyCountTextScale);
	// チュートリアルエリアの倒すエネミーの数のUIを生成
	DefeatEnemyNumberText* defeatTutorialEnemyNumberTextPtr = new DefeatEnemyNumberText(MDefeatEnemyNumberTextPosition, Tag::eOther, State::eActive, 101, MTutorialDefeatEnemyNum, _enemysControlerPtr, MDefeatEnemyNumberTextScale);
	// 無限にエネミーが湧いてくるエリアの倒すエネミーの数のUIを生成
	DefeatEnemyNumberText* defeatInfinitelyEnemyNumberTextPtr = new DefeatEnemyNumberText(MDefeatEnemyNumberTextPosition, Tag::eOther, State::eDead, 102, MInfinitelyDefeatEnemyNum, _enemysControlerPtr, MDefeatEnemyNumberTextScale);

	// ボスのhpゲージを有効にするコンポーネントを生成
	new DeadObjectEnable(this, _bossActiveBoxPtr, bossHitPointGaugePtr);
	// ボスのhpの枠を有効にするコンポーネントを生成
	new DeadObjectEnable(this, _bossActiveBoxPtr, bossHitPointFramePtr);
	// 倒したエネミーのカウントUIを有効にするコンポーネントを生成
	new DeadObjectEnable(this, _enemyActiveBoxPtr, deadInfinitelyEnemyCountTextPtr);
	// 無限にエネミーが湧いてくるエリアの倒すエネミーの数のUIを有効にするコンポーネントを生成
	new DeadObjectEnable(this, _enemyActiveBoxPtr, defeatInfinitelyEnemyNumberTextPtr);
}