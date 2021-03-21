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
@brief  コンストラクタ
*/
Game::Game()
	: fps(nullptr)
    , isRunning(true)
	, isScene(false)
	, inputSystem(0)
{
}

/*
@brief  デストラクタ
*/
Game::~Game()
{
}

/*
@brief  初期化処理
@return true : 成功 , false : 失敗
*/
bool Game::Initialize()
{
	//SDLの初期化
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

    //入力管理クラスの初期化
	inputSystem = new InputSystem();
	if (!inputSystem->Initialize())
	{
		SDL_Log("Failed to initialize input system");
		return false;
	}
	//レンダラーの初期化
	Renderer::CreateInstance();
	//画面作成
	if (!RENDERER->Initialize(1080, 800, false))
	{
		SDL_Log("Failed to initialize renderer");
		Renderer::DeleteInstance();
		return false;
	}

    //当たり判定用クラスの初期化
	PhysicsWorld::CreateInstance();
	
	//FPS管理クラスの初期化
	fps = new FPS();

    //ゲームオブジェクト管理クラスの初期化
    GameObjectManager::CreateInstance();

	Matrix4 v = Matrix4::CreateLookAt(Vector3(200, 0, -500), Vector3(200,0, 0),Vector3::UnitY);
	RENDERER->SetViewMatrix(v);

	/*stage01Scene = new Stage01Scene();*/

	return true;
}

/*
@brief  終了処理
*/
void Game::Termination()
{
    //データのアンロード
	UnloadData();
    //スタティッククラスの解放処理
    GameObjectManager::DeleteInstance();
	Renderer::DeleteInstance();
	PhysicsWorld::DeleteInstance();
    //クラスの解放処理
    delete fps;
    delete inputSystem;
    //サブシステムの終了
	SDL_Quit();
}

void Game::SetFirstScene(SceneBase* firstScene)
{
	mNowScene = firstScene;
}

/*
@brief  ゲームループ
*/
void Game::GameLoop()
{
	while (isRunning)
	{
		ProcessInput();

		SceneBase* tmpScene;

		// 実行中のシーンを更新
		tmpScene = mNowScene->update();

		// シーンの切り替えが発生した？
		if (tmpScene != mNowScene)
		{
			// 現在のシーンの解放
    		delete mNowScene;

			// 現在実行中のシーンの切り替え
			mNowScene = tmpScene;
			continue;
		}

		UpdateGame();
		/*GenerateOutput();*/

		// 現在のシーンの描画処理
		mNowScene->draw();

		fps->Update();
	}

	// シーンの解放
	if (mNowScene)
	{
		delete mNowScene;
		mNowScene = nullptr;
	}
}

/*
@brief   ロードしたデータの解放
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
@brief  入力関連の処理
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
@brief  描画関連の処理
*/
void Game::GenerateOutput()
{
	RENDERER->Draw();
}

/*
@brief  ゲームのアップデート処理
*/
void Game::UpdateGame()
{
	float deltaTime = fps->GetDeltaTime();
	
	GAME_OBJECT_MANAGER->UpdateGameObject(deltaTime);
}