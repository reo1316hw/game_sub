#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameOverScene::GameOverScene()
	: MSpriteScale(Vector3(2.0f, 1.0f, 1.0f))
{
	// ライトを設定(設定しないと何も映らない)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(1.0f, 0.7f, -0.7f);
	dir.m_diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	// ゲームオーバー用のスプライトを生成
	mSprite = new Sprite("Assets/Texture/GameOver.png", true, MSpriteScale);
}

/// <summary>
/// デストラクタ
/// </summary>
GameOverScene::~GameOverScene()
{
	delete mSprite;
}

/// <summary>
/// シーンの更新
/// </summary>
/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
/// <returns> シーンクラスのポインタ </returns>
SceneBase* GameOverScene::Update(const InputState& _KeyState)
{
	// アクションシーンに遷移
	if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_START) == Released ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Released)
	{
		return new TitleScene();
	}

	return this;
}