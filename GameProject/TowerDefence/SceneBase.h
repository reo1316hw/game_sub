#pragma once

// �O���錾
class Sprite;
class MapCreate;
class Goal;
struct InputState;

class SceneBase
{
public:

    SceneBase();

    // �������z�֐��Ń|�����[�t�B�Y��������Ƃ��A
    // �f�X�g���N�^�͕K��virtual�ɂ���
    virtual ~SceneBase() {};

    virtual SceneBase* Update(const InputState& _KeyState) = 0; // �������z�֐� virtual �߂�l�@���\�b�h��() = 0;

protected:

    Sprite*      mSprite;
    MapCreate*    mMapCreate;
    Goal*         mGoalLine;

private:
};