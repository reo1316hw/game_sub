#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
ActionScene::ActionScene()
	: MTimingTransitionGameClear(220.0f)
	, MTimingTransitionGameOver(160.0f)
	, MAngleOfView(70.0f)
	, mGameClearTransitionUntilCount(0)
	, mGameOverTransitionUntilCount(0)
	, mPlayerPtr(nullptr)
	, mBossPtr(nullptr)
	, mMainCameraPtr(nullptr)
{
	// ライトを設定(設定しないと何も映らない)
	RENDERER->SetAmbientLight(Vector3(0.8f, 0.8f, 0.8f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(0.0f, 0.0f, 1.0f);
	dir.m_diffuseColor = Vector3(0.36f, 0.44f, 0.5f);
	dir.m_specColor = Vector3(0.4f, 0.4f, 0.4f);

	// 行列初期化
	Matrix4 proj;
	proj = Matrix4::CreatePerspectiveFOV(Math::ToRadians(MAngleOfView), RENDERER->GetScreenWidth(), RENDERER->GetScreenHeight(), 1.0, 10000.0f);
	RENDERER->SetProjMatrix(proj);

	// マップを生成するためのクラスを生成
    mMapCreate = new MapCreate();
	mMapCreate->OpenFile();
	mPlayerPtr = mMapCreate->GetPlayerPtr();
	mBossPtr = mMapCreate->GetBossPtr();
	// エネミーを管理するクラスのポインタ
	EnemyObjectManager* enemyObjectManagerPtr = mMapCreate->GetEnemyObjectManagerPtr();
	// エネミーを更新させるための当たり判定用矩形オブジェクトのポインタ
	DeadObjectActiveBox* enemyActiveBoxPtr = mMapCreate->GetEnemyActiveBoxPtr();
	// ボスを更新させるための当たり判定用矩形オブジェクトのポインタ
	DeadObjectActiveBox* bossActiveBoxPtr = mMapCreate->GetBossActiveBoxPtr();

	// カメラ生成
	mMainCameraPtr = new MainCameraObject(mPlayerPtr, mBossPtr, true);
	// UIの親クラス
	new UIRoot(Tag::eOther, mPlayerPtr, mBossPtr, enemyObjectManagerPtr, enemyActiveBoxPtr, bossActiveBoxPtr);

	// プレイヤークラスでカメラのポインタを設定
	mPlayerPtr->SetMainCameraPtr(mMainCameraPtr);

	// スカイボックス生成
	new SkyBoxObject(Tag::eOther, false);
}

/// <summary>
/// デストラクタ
/// </summary>
ActionScene::~ActionScene()
{
	GAME_OBJECT_MANAGER->RemoveAllUsedGameObject();
}

/// <summary>
/// シーンの更新
/// </summary>
/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
/// <returns> シーンクラスのポインタ </returns>
SceneBase* ActionScene::Update(const InputState& _KeyState)
{
	// ボスのhpが0になったらゲームクリアシーンへ遷移
	if (mBossPtr->GetHitPoint() <= 0)
	{
		++mGameClearTransitionUntilCount;
	}

	if (mGameClearTransitionUntilCount >= MTimingTransitionGameClear)
	{
		return new GameClearScene();
	}
	
	// プレイヤーのhpが0になったらゲームオーバーシーンへ遷移
	if (mPlayerPtr->GetHitPoint() <= 0)
	{
		++mGameOverTransitionUntilCount;
	}

	if (mGameOverTransitionUntilCount >= MTimingTransitionGameOver)
	{
		return new GameOverScene();
	}

	// 当たり判定を可視化させるデバッグモードの切り替え
	if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_0) == Released)
	{
		PHYSICS->ToggleDebugMode();
	}

	RENDERER->GetEffekseerManager()->Update();

	return this;
}
