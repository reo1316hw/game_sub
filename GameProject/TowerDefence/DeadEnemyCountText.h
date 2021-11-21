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
    /// <param name="_enemysControlerPtr"> エネミーたちを制御するクラスのポインタ </param>
    /// <param name="_Scale"> テクスチャの拡大サイズ </param>
    DeadEnemyCountText(const Vector3& _Pos, const Tag& _ObjectTag,
        EnemysControler* _enemysControlerPtr, const Vector3& _Scale = Vector3(1.0f, 1.0f, 1.0f));

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~DeadEnemyCountText() {};

private:

    // 最初に倒すエネミーの数
    const int MFirstDefeatEnemyNum;
    // 次に倒すエネミーの数
    const int MNextDefeatEnemyNum;
};