#pragma once
#include <SDL.h>
#include <unordered_map>
#include <vector>
#include <string>
#include "SceneBase.h"

// �O���錾
class FPS;
class GameObject;
class InputSystem;

/*
@file Game.h
@brief �Q�[���̐i�s���s��
*/
class Game
{
public:
	Game();
	~Game();

	/*
	@brief	����������
	@return true : ����, false : ���s
	*/
	bool Initialize();
	/*
	@brief  �I������
	*/
	void Termination();
	/*
	@brief  �Q�[�����[�v
	*/
	void GameLoop();
	// �ŏ��̃V�[�������߂�֐�
	void SetFirstScene(SceneBase* _firstScene);

	/*bool GetScene() { return isScene; };

	void SetScene(bool _isScene) { isScene = _isScene; };*/

	//�V�[����؂�ւ��邩
	bool mSceneFlag;

	static int mDebug;
private:
	SceneBase* mNowScene;
	/*Stage01Scene* stage01Scene;*/

	/*
	@brief  ���͊֘A�̏���
	*/
    void ProcessInput();
	/*
	@brief  �`��֘A�̏���
	*/
    virtual void GenerateOutput();

	/*
	@brief  �Q�[���̍X�V����
	*/
	void UpdateGame();

	/*
	@brief   ���[�h�����f�[�^�̉��
	*/
	void UnloadData();

	// FPS�v���N���X
	FPS* mFps;
    // ���͊Ǘ��N���X
	InputSystem* mInputSystem;
	//�Q�[���𑱂��邩�ǂ���
    bool mRunningFlag;
};

