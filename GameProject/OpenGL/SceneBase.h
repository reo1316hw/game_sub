#pragma once

// 前方宣言
class Sprite;
class InputSystem;
class MapCreate;
class HeartUI;
class Goal;
class PlayerObject;

class SceneBase
{
public:
    SceneBase() {};

    // 純粋仮想関数でポリモーフィズムさせるとき、
    // デストラクタは必ずvirtualにする
    virtual ~SceneBase() {};

    virtual SceneBase* update() = 0; // 純粋仮想関数 virtual 戻り値　メソッド名() = 0;

    static int  GetScene() { return mIsScene; };
    virtual void SetScene(int _isScene) { mIsScene = _isScene; }; //シーンをセット

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
    Sprite*      mSprite;
    //入力管理クラス
    InputSystem* mInputSystem;

    MapCreate*    mMapCreate;
    PlayerObject* mPlayer;
    Goal*         mGoalLine;
    HeartUI*      mHeartUI;

    bool         mClearFlag;

    int          mNextSceneCount;

private:
    static int   mIsScene;
};