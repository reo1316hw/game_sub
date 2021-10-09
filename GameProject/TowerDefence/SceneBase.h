#pragma once

// �O���錾
class Sprite;
class InputSystem;
class MapCreate;
class HeartUI;
class Goal;
class PlayerObject;
struct InputState;


class SceneBase
{
public:
    SceneBase() {};

    // �������z�֐��Ń|�����[�t�B�Y��������Ƃ��A
    // �f�X�g���N�^�͕K��virtual�ɂ���
    virtual ~SceneBase() {};

    virtual SceneBase* Update(const InputState& _KeyState) = 0; // �������z�֐� virtual �߂�l�@���\�b�h��() = 0;

    static int  GetScene() { return mIsScene; };
    virtual void SetScene(int _isScene) { mIsScene = _isScene; }; //�V�[�����Z�b�g

    enum Scene
    {
        // ���̑�
        other,
        // �^�C�g��
        title,
        // �`���[�g���A��
        tutorial,
        // �X�e�[�W�Z���N�g���
        stageSelect,
        // �X�e�[�W1
        stage01,
        // �X�e�[�W2
        stage02,
        // �Q�[���N���A
        gameClear,
        // �Q�[���I�[�o�[
        gameOver,
        // �R���e�B�j���[ 
        Continue
    };

protected:
    Sprite*      mSprite;
    //���͊Ǘ��N���X
    InputSystem* mInputSystem;

    MapCreate*    mMapCreate;
    Goal*         mGoalLine;
    HeartUI*      mHeartUI;

    bool         mClearFlag;

    int          mNextSceneCount;

private:
    static int   mIsScene;
};