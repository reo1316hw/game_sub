#include "pch.h"

TitleScene::TitleScene()
{
	// ƒ‰ƒCƒg‚ðÝ’è(Ý’è‚µ‚È‚¢‚Æ‰½‚à‰f‚ç‚È‚¢)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(1.0f, 0.7f, -0.7f);
	dir.m_diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	/*mEmissiveTexture = RENDERER->GetTexture("Assets/title.png");
	mTexture->SetLuminace(1.0f);*/
	//mSprite->SetTexture(mTexture, mEmissiveTexture);

	mSprite = new Sprite("Assets/Texture/Wall.png");
}

TitleScene::~TitleScene()
{
	delete mSprite;
}

SceneBase* TitleScene::Update(const InputState& _KeyState)
{
	if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_START) == Released ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Released)
	{
 		return new Tutorial();
	}

	return this;
}