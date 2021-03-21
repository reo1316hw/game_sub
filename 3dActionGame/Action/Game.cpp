#include "Game.h"
#include "SDL.h"
#include <glew.h>
#include <algorithm>
#include "FPS.h"
#include "Renderer.h"
#include "InputSystem.h"
#include "PhysicsWorld.h"
#include "GameObjectManager.h"

int Game::debug = 0;

/*
@brief  �R���X�g���N�^
*/
Game::Game()
	: fps(nullptr)
    , isRunning(true)
	, isScene(false)
	, inputSystem(0)
{
}

/*
@brief  �f�X�g���N�^
*/
Game::~Game()
{
}

/*
@brief  ����������
@return true : ���� , false : ���s
*/
bool Game::Initialize()
{
	//SDL�̏�����
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

    //���͊Ǘ��N���X�̏�����
	inputSystem = new InputSystem();
	if (!inputSystem->Initialize())
	{
		SDL_Log("Failed to initialize input system");
		return false;
	}
	//�����_���[�̏�����
	Renderer::CreateInstance();
	//��ʍ쐬
	if (!RENDERER->Initialize(1080, 800, false))
	{
		SDL_Log("Failed to initialize renderer");
		Renderer::DeleteInstance();
		return false;
	}

    //�����蔻��p�N���X�̏�����
	PhysicsWorld::CreateInstance();
	
	//FPS�Ǘ��N���X�̏�����
	fps = new FPS();

    //�Q�[���I�u�W�F�N�g�Ǘ��N���X�̏�����
    GameObjectManager::CreateInstance();

	Matrix4 v = Matrix4::CreateLookAt(Vector3(200, 0, -500), Vector3(200,0, 0),Vector3::UnitY);
	RENDERER->SetViewMatrix(v);

	/*stage01Scene = new Stage01Scene();*/

	return true;
}

/*
@brief  �I������
*/
void Game::Termination()
{
    //�f�[�^�̃A�����[�h
	UnloadData();
    //�X�^�e�B�b�N�N���X�̉������
    GameObjectManager::DeleteInstance();
	Renderer::DeleteInstance();
	PhysicsWorld::DeleteInstance();
    //�N���X�̉������
    delete fps;
    delete inputSystem;
    //�T�u�V�X�e���̏I��
	SDL_Quit();
}

void Game::SetFirstScene(SceneBase* firstScene)
{
	mNowScene = firstScene;
}

/*
@brief  �Q�[�����[�v
*/
void Game::GameLoop()
{
	while (isRunning)
	{
		ProcessInput();

		SceneBase* tmpScene;

		// ���s���̃V�[�����X�V
		tmpScene = mNowScene->update();

		// �V�[���̐؂�ւ������������H
		if (tmpScene != mNowScene)
		{
			// ���݂̃V�[���̉��
    		delete mNowScene;

			// ���ݎ��s���̃V�[���̐؂�ւ�
			mNowScene = tmpScene;
			continue;
		}

		UpdateGame();
		/*GenerateOutput();*/

		// ���݂̃V�[���̕`�揈��
		mNowScene->draw();

		fps->Update();
	}

	// �V�[���̉��
	if (mNowScene)
	{
		delete mNowScene;
		mNowScene = nullptr;
	}
}

/*
@brief   ���[�h�����f�[�^�̉��
*/
void Game::UnloadData()
{
	if (RENDERER != nullptr)
	{
		RENDERER->UnloadData();
		RENDERER->Shutdown();
	}
}

/*
@brief  ���͊֘A�̏���
*/
void Game::ProcessInput()
{
	inputSystem->PrepareForUpdate();

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEWHEEL:
			inputSystem->ProcessEvent(event);
			break;
		default:
			break;
		}
	}

	inputSystem->Update();
	const InputState& state = inputSystem->GetState();

	if (state.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_BACK)  ||
		state.Keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == Released)
	{
		isRunning = false;
	}

	/*if (state.Keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == Released)
	{
		isRunning = false;
	}*/


	GAME_OBJECT_MANAGER->ProcessInput(state);
}

/*
@brief  �`��֘A�̏���
*/
void Game::GenerateOutput()
{
	RENDERER->Draw();
}

/*
@brief  �Q�[���̃A�b�v�f�[�g����
*/
void Game::UpdateGame()
{
	float deltaTime = fps->GetDeltaTime();
	
	GAME_OBJECT_MANAGER->UpdateGameObject(deltaTime);
}