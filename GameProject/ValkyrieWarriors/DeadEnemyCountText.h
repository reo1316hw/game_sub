#pragma once

/// <summary>
/// 倒したエネミーのカウントUI
/// </summary>
class DeadEnemyCountText : public GameObject
{
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="_Pos"> UIの生成場所(スクリーン座標) </param>
    /// <param name="_ObjectTag"> アタッチしたゲームオブジェクトのタグ </param>
    /// <param name="_enemyObjectManagerPtr"> エネミーを管理するクラスの基底クラスのポインタ </param>
    /// <param name="_Scale"> テクスチャの拡大サイズ </param>
    DeadEnemyCountText(const Vector3& _Pos, const Tag& _ObjectTag,
        EnemyObjectManager* _enemyObjectManagerPtr, const Vector3& _Scale = Vector3(1.0f, 1.0f, 1.0f));

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~DeadEnemyCountText() {};

private:
};