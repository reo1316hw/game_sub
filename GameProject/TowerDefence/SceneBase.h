#pragma once

// 前方宣言
class Sprite;
class MapCreate;
class Goal;
struct InputState;

class SceneBase
{
public:

    SceneBase();

    // 純粋仮想関数でポリモーフィズムさせるとき、
    // デストラクタは必ずvirtualにする
    virtual ~SceneBase() {};

    virtual SceneBase* Update(const InputState& _KeyState) = 0; // 純粋仮想関数 virtual 戻り値　メソッド名() = 0;

protected:

    Sprite*      mSprite;
    MapCreate*    mMapCreate;
    Goal*         mGoalLine;

private:
};