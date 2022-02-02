#pragma once

/// <summary>
/// 倒すエネミーの数のUI
/// </summary>
class DefeatEnemyNumberText : public GameObject
{
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="_Pos"> UIの生成場所(スクリーン座標) </param>
    /// <param name="_ObjectTag"> アタッチしたゲームオブジェクトのタグ </param>
    /// <param name="_State"> ゲームオブジェクトの状態 </param>
    /// <param name="_FontDataNum"> フォントテクスチャ配列の要素数 </param>
    /// <param name="_enemyObjectManagerPtr"> エネミーを管理するクラスの基底クラスのポインタ </param>
    /// <param name="_Scale"> テクスチャの拡大サイズ </param>
    DefeatEnemyNumberText(const Vector3& _Pos, const Tag& _ObjectTag, const State& _State, const int& _FontDataNum,
        EnemyObjectManager* _enemyObjectManagerPtr, const Vector3& _Scale = Vector3(1.0f, 1.0f, 1.0f));

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~DefeatEnemyNumberText() {};

private:
};