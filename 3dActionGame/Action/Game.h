#pragma once

#include "SDL.h"
#include "SceneBase.h"
#include <unordered_map>
#include <vector>
#include <string>

class FPS;
class GameObject;
class InputSystem;

enum SceneState
{

};

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
	void SetFirstScene(SceneBase* firstScene);

	/*bool GetScene() { return isScene; };

	void SetScene(bool _isScene) { isScene = _isScene; };*/

	//�V�[����؂�ւ��邩
	bool isScene;

	static int debug;
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
	@brief  �Q�[���̃A�b�v�f�[�g����
	*/
	void UpdateGame();

	/*
	@brief   ���[�h�����f�[�^�̉��
	*/
	void UnloadData();

	// FPS�v���N���X
	FPS* fps;
    // ���͊Ǘ��N���X
	InputSystem* inputSystem;
	//�Q�[���𑱂��邩�ǂ���
    bool isRunning;
};

