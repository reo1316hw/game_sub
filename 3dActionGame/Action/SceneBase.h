#pragma once

class Sprite;
class InputSystem;

class SceneBase
{
public:
    SceneBase() {};

    // �������z�֐��Ń|�����[�t�B�Y��������Ƃ��A
    // �f�X�g���N�^�͕K��virtual�ɂ���
    virtual ~SceneBase() {};

    virtual SceneBase* update() = 0; // �������z�֐� virtual �߂�l�@���\�b�h��() = 0;
    virtual void draw() = 0;         // �������z�֐�

    static int  GetScene() { return isScene; };
    virtual void SetScene(int _isScene) { isScene = _isScene; }; //�V�[�����Z�b�g

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
    Sprite* sprite;
    InputSystem* inputSystem;

    bool clearFlag;

private:
    static int isScene;
};