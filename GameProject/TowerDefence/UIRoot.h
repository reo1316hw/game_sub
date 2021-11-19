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
    /// <param name="_enemyActiveBoxPtr"> エネミーを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
    /// <param name="_bossActiveBoxPtr"> ボスを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
    /// <param name="_enemysControlerPtr"> エネミーたちを制御するクラスのポインタ </param>
	UIRoot(const Tag& _ObjectTag, PlayerObject* _playerPtr, BossObject* _bossPtr, DeadObjectActiveBox* _enemyActiveBoxPtr,
        DeadObjectActiveBox* _bossActiveBoxPtr, EnemysControler* _enemysControlerPtr);

    /// <summary>
    /// デストラクタ
    /// </summary>
	~UIRoot() {};

private:

    // チュートリアルエリアで倒すエネミーの数
    const int MTutorialDefeatEnemyNum;
    // 無限にエネミーが湧いてくるエリアで倒すエネミーの数
    const int MInfinitelyDefeatEnemyNum;

    // プレイヤーのhpゲージの座標
    const Vector3 MPlayerHitPointPosition;
    // ボスのhpゲージの座標
    const Vector3 MBossHitPointPosition;
    // 倒したエネミーのカウントUIの座標
    const Vector3 MDeadEnemyCountTextPosition;
    // 倒すエネミーの数のUIの座標
    const Vector3 MDefeatEnemyNumberTextPosition;
    // プレイヤーのhpゲージの大きさ
    const Vector3 MPlayerHitPointScale;
    // ボスのhpゲージの大きさ
    const Vector3 MBossHitPointScale;
    // 倒したエネミーのカウントUIの大きさ
    const Vector3 MDeadEnemyCountTextScale;
    // 倒すエネミーの数のUIの大きさ
    const Vector3 MDefeatEnemyNumberTextScale;
};