#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameClearScene::GameClearScene()
	: MSpriteScale(Vector3(2.0f, 1.0f, 1.0f))
	, MTimingTransitionTitle(120)
	, mTitleTransitionUntilCount(0)
{
	// ライトを設定(設定しないと何も映らない)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(1.0f, 0.7f, -0.7f);
	dir.m_diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	// ゲームクリア用のスプライトを生成
	mSprite = new Sprite("Assets/Texture/GameClear.png", true, 1.0f, MSpriteScale);
}

/// <summary>
/// デストラクタ
/// </summary>
GameClearScene::~GameClearScene()
{
	delete mSprite;
}

/// <summary>
/// シーンの更新
/// </summary>
/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
/// <returns> シーンクラスのポインタ </returns>
SceneBase* GameClearScene::Update(const InputState& _KeyState)
{
	++mTitleTransitionUntilCount;

	// タイトルシーンに遷移
	if (mTitleTransitionUntilCount >= MTimingTransitionTitle)
	{
		return new TitleScene();
	}

	return this;
}