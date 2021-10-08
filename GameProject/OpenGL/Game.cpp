#include "pch.h"

int Game::mDebug = 0;

/*
@brief  コンストラクタ
*/
Game::Game()
	: mFps(nullptr)
    , mRunningFlag(true)
	, mSceneFlag(false)
	, mInputSystem(0)
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
	mInputSystem = new InputSystem();
	if (!mInputSystem->Initialize())
	{
		SDL_Log("Failed to initialize input system");
		return false;
	}
	//レンダラーの初期化
	Renderer::CreateInstance();
	//画面作成
	if (!RENDERER->Initialize(1920, 1080, false))
	{
		SDL_Log("Failed to initialize renderer");
		Renderer::DeleteInstance();
		return false;
	}

    //当たり判定用クラスの初期化
	PhysicsWorld::CreateInstance();
	
	//FPS管理クラスの初期化
	mFps = new FPS();

    //ゲームオブジェクト管理クラスの初期化
    GameObjectManager::CreateInstance();

	Matrix4 v = Matrix4::CreateLookAt(Vector3(200, 0, -500), Vector3(200,0, 0),Vector3::UnitY);
	RENDERER->SetViewMatrix(v);

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
    delete mFps;
    delete mInputSystem;
    //サブシステムの終了
	SDL_Quit();
}

void Game::SetFirstScene(SceneBase* _firstScene)
{
	mNowScene = _firstScene;
}

/*
@brief  ゲームループ
*/
void Game::GameLoop()
{
	while (mRunningFlag)
	{
		//入力関連の処理
		const InputState& state = ProcessInput();

		SceneBase* tmpScene;

		// 実行中のシーンを更新処理
		tmpScene = mNowScene->Update(state);

		// シーンの切り替えが発生した？
		if (tmpScene != mNowScene)
		{
			// 現在のシーンの解放
    		delete mNowScene;

			// 現在実行中のシーンの切り替え
 			mNowScene = tmpScene;
			continue;
		}
		
		//ゲームの更新処理
		UpdateGame();
		// 現在のシーンの描画処理
		GenerateOutput();
		//FPSの更新処理
		mFps->Update();
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
InputState Game::ProcessInput()
{
	mInputSystem->PrepareForUpdate();

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mRunningFlag = false;
			break;
		case SDL_MOUSEWHEEL:
			mInputSystem->ProcessEvent(event);
			break;
		default:
			break;
		}
	}

	mInputSystem->Update();
	const InputState& state = mInputSystem->GetState();

	if (state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_BACK)  ||
		state.m_keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == Released)
	{
		mRunningFlag = false;
	}

	GAME_OBJECT_MANAGER->ProcessInput(state);

	return state;
}

/*
@brief  描画関連の処理
*/
void Game::GenerateOutput()
{
	RENDERER->Draw();
}

/*
@brief  ゲームの更新処理
*/
void Game::UpdateGame()
{
	float deltaTime = mFps->GetDeltaTime();
	
	GAME_OBJECT_MANAGER->UpdateGameObject(deltaTime);
}