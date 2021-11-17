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
    /// <param name="_bossActiveBoxPtr"> ボスを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
	UIRoot(const Tag& _ObjectTag, PlayerObject* _playerPtr,
        BossObject* _bossPtr, BossActiveBox* _bossActiveBoxPtr);

    /// <summary>
    /// デストラクタ
    /// </summary>
	~UIRoot() {};

private:

    // プレイヤーのhpゲージの大きさ
    const Vector2 MPlayerHitPointScale;
    // ボスのhpゲージの大きさ
    const Vector2 MBossHitPointScale;
    // プレイヤーのhpゲージの座標
    const Vector3 MPlayerHitPointPosition;
    // ボスのhpゲージの座標
    const Vector3 MBossHitPointPosition;
};