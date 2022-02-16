#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
ActionScene::ActionScene()
	: MPlusAlpha(0.006f)
	, MAngleOfView(70.0f)
	, MLightDistance(100.0f)
	, MSpriteScale(Vector3(2.0f, 1.0f, 1.0f))
	, mPlayerPtr(nullptr)
	, mBossPtr(nullptr)
	, mMainCameraPtr(nullptr)
{
	// ライトを設定(設定しないと何も映らない)
	RENDERER->SetAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(-0.5f, 0.5f, -0.5f);
	//dir.m_diffuseColor = Vector3(0.35f, 0.45f, 0.5f);
	dir.m_diffuseColor = Vector3(0.35f, 0.45f, 0.5f);
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

	// 門のリスト
	std::vector<GateObject*> gateList = mMapCreate->GetGateList();
	// エネミーを管理するクラスのポインタ
	EnemyObjectManager* enemyObjectManagerPtr = mMapCreate->GetEnemyObjectManagerPtr();
	// エネミーを更新させるための当たり判定用矩形オブジェクトのポインタ
	DeadObjectActiveBox* enemyActiveBoxPtr = mMapCreate->GetEnemyActiveBoxPtr();
	// ボスを更新させるための当たり判定用矩形オブジェクトのポインタ
	DeadObjectActiveBox* bossActiveBoxPtr = mMapCreate->GetBossActiveBoxPtr();

	// カメラ生成
	mMainCameraPtr = new MainCameraObject(mPlayerPtr, mBossPtr, gateList, true);
	// UIの親クラス
	new UIRoot(Tag::eOther, mPlayerPtr, mBossPtr, enemyObjectManagerPtr, enemyActiveBoxPtr, bossActiveBoxPtr);

	// プレイヤークラスでカメラのポインタを設定
	mPlayerPtr->SetMainCameraPtr(mMainCameraPtr);

	// スカイボックス生成
	new SkyBoxObject(Tag::eOther, false);

	// スプライトのリスト
	std::vector<Sprite*> spriteList;

	// フェードイン用の白テクスチャ
	spriteList.emplace_back(new Sprite("Assets/Texture/FadeWhite.png", true, 0.0f, MSpriteScale));
	// フェードイン用の黒テクスチャ
	spriteList.emplace_back(new Sprite("Assets/Texture/FadeBlack.png", true, 0.0f, MSpriteScale));

	for (auto spriteItr : spriteList)
	{
		mSpriteComponentList.emplace_back(spriteItr->GetSpriteComponentPtr());
	}
}

/// <summary>
/// デストラクタ
/// </summary>
ActionScene::~ActionScene()
{
	mSpriteComponentList.clear();
	GAME_OBJECT_MANAGER->RemoveAllUsedGameObject();
}

/// <summary>
/// シーンの更新
/// </summary>
/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
/// <returns> シーンクラスのポインタ </returns>
SceneBase* ActionScene::Update(const InputState& _KeyState)
{
	// フェードイン用の白テクスチャの透明度
	float whiteSpriteAlpha = 0.0f;
	// フェードイン用の黒テクスチャの透明度
	float blackSpriteAlpha = 0.0f;

	// ボスのhpが0になったら白いフェードインを始める
	if (mBossPtr->GetHitPoint() <= 0)
	{
		whiteSpriteAlpha = mSpriteComponentList[FadeInSpriteType::eWhite]->IncreaseAlpha(MPlusAlpha);
	}

	// ゲームクリアシーンへ遷移する
	if (whiteSpriteAlpha >= 1.0f)
	{
		mSpriteComponentList[FadeInSpriteType::eWhite]->ResetAlpha();
		// エフェクトを全て止める
		RENDERER->GetEffekseerManager()->StopAllEffects();
		return new GameClearScene();
	}
	
	// プレイヤーのhpが0になったら黒いフェードインを始める
	if (mPlayerPtr->GetHitPoint() <= 0)
	{
		blackSpriteAlpha = mSpriteComponentList[FadeInSpriteType::eBlack]->IncreaseAlpha(MPlusAlpha);
	}

	// ゲームオーバーシーンへ遷移する
	if (blackSpriteAlpha >= 1.0f)
	{
		mSpriteComponentList[FadeInSpriteType::eBlack]->ResetAlpha();
		// エフェクトを全て止める
		RENDERER->GetEffekseerManager()->StopAllEffects();
		return new GameOverScene();
	}

	// 当たり判定を可視化させるデバッグモードの切り替え
	if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_0) == Released)
	{
		PHYSICS->ToggleDebugMode();
	}

	// プレイヤーの座標を取得
	Vector3 playerPos = mPlayerPtr->GetPosition();

	// レンダラに登録されているディレクショナルライト方向を取得
	DirectionalLight dirLight = RENDERER->GetDirectionalLight();
	Vector3 lightDir = dirLight.m_direction;
	lightDir.Normalize();

	// シャドウマップレンダリングのためのライト情報渡す
	RENDERER->SetDepthSetting(playerPos, lightDir, Vector3::UnitZ, MLightDistance);

	RENDERER->GetEffekseerManager()->Update();

	return this;
}
