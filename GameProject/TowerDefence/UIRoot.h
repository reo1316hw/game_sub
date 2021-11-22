#pragma once

// 前方宣言
class BossHitPointGauge;
class BossHitPointFrame;

/// <summary>
/// UIをまとめるための親クラス
/// </summary>
class UIRoot : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	/// <param name="_bossPtr"> ボスのポインタ </param>
    /// <param name="_enemyObjectManagerPtr"> エネミーを管理するクラスのポインタ </param>
    /// <param name="_enemyActiveBoxPtr"> エネミーを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
    /// <param name="_bossActiveBoxPtr"> ボスを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
	UIRoot(const Tag& _ObjectTag, PlayerObject* _playerPtr, BossObject* _bossPtr,
        EnemyObjectManager* _enemyObjectManagerPtr, DeadObjectActiveBox* _enemyActiveBoxPtr,
        DeadObjectActiveBox* _bossActiveBoxPtr);

    /// <summary>
    /// デストラクタ
    /// </summary>
	~UIRoot() {};

private:

    // プレイヤーのhpゲージの大きさ
    const Vector3 MPlayerHitPointScale;
    // ボスのhpゲージの大きさ
    const Vector3 MBossHitPointScale;
    // 倒したエネミーのカウントゲージの大きさ
    const Vector3 MDeadEnemyCountScale;
    // 倒したエネミーのカウントテキストの大きさ
    const Vector3 MDeadEnemyCountTextScale;
    // 倒すエネミーの数のテキストの大きさ
    const Vector3 MDefeatEnemyNumberTextScale;
    // 操作説明UIの大きさ
    const Vector3 MOperationExplanationScale;
    // プレイヤーのhpゲージの座標
    const Vector3 MPlayerHitPointPosition;
    // ボスのhpゲージの座標
    const Vector3 MBossHitPointGaugePosition;
    // ボスのhpフレームの座標
    const Vector3 MBossHitPointFramePosition;
    // 倒したエネミーのカウントゲージの座標
    const Vector3 MDeadEnemyCountGaugePosition;
    // 倒したエネミーのカウントフレームの座標
    const Vector3 MDeadEnemyCountFramePosition;
    // 倒したエネミーのカウントテキストの座標
    const Vector3 MDeadEnemyCountTextPosition;
    // 倒すエネミーの数のテキストの座標
    const Vector3 MDefeatEnemyNumberTextPosition;
    // 操作説明UIの座標
    const Vector3 MOperationExplanationtPosition;
};