#pragma once

// 前方宣言
class Sprite;
class MapCreate;
struct InputState;

/// <summary>
/// シーンの基底クラス
/// </summary>
class SceneBase
{
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    SceneBase();
    
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SceneBase() {};

    /// <summary>
    /// シーンの更新
    /// </summary>
    /// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
    /// <returns> シーンクラスのポインタ </returns>
    virtual SceneBase* Update(const InputState& _KeyState) = 0;

protected:

    // スプライトのポインタ
    Sprite*      mSprite;
    // マップを生成するクラスのポインタ
    MapCreate*    mMapCreate;

private:
};