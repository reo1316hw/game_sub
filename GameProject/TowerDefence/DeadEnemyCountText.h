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
    /// <param name="_State"> ゲームオブジェクトの状態 </param>
    /// <param name="_DefeatEnemyNum">  倒すエネミーの数 </param>
    /// <param name="_enemysControlerPtr"> エネミーたちを制御するクラスのポインタ </param>
    /// <param name="_Scale"> テクスチャの拡大サイズ </param>
    DeadEnemyCountText(const Vector3& _Pos, const Tag& _ObjectTag, const State& _State, const int& _DefeatEnemyNum, 
        EnemysControler* _enemysControlerPtr, const Vector3& _Scale = Vector3(1.0f, 1.0f, 1.0f));

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~DeadEnemyCountText() {};

private:
};