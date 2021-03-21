#pragma once

class Sprite;
class InputSystem;

class SceneBase
{
public:
    SceneBase() {};

    // 純粋仮想関数でポリモーフィズムさせるとき、
    // デストラクタは必ずvirtualにする
    virtual ~SceneBase() {};

    virtual SceneBase* update() = 0; // 純粋仮想関数 virtual 戻り値　メソッド名() = 0;
    virtual void draw() = 0;         // 純粋仮想関数

    static int  GetScene() { return isScene; };
    virtual void SetScene(int _isScene) { isScene = _isScene; }; //シーンをセット

    enum Scene
    {
        // その他
        other,
        // タイトル
        title,
        // チュートリアル
        tutorial,
        // ステージセレクト画面
        stageSelect,
        // ステージ1
        stage01,
        // ステージ2
        stage02,
        // ゲームクリア
        gameClear,
        // ゲームオーバー
        gameOver,
        // コンティニュー 
        Continue
    };
protected:
    Sprite* sprite;
    InputSystem* inputSystem;

    bool clearFlag;

private:
    static int isScene;
};