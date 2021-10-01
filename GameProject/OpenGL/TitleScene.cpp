#include "TitleScene.h"
#include "Tutorial.h"
#include "Renderer.h"
#include "GameObject.h"
#include "InputSystem.h"
#include "Sprite.h"

TitleScene::TitleScene(const Scene& _scene)
{
	// ƒ‰ƒCƒg‚ðÝ’è(Ý’è‚µ‚È‚¢‚Æ‰½‚à‰f‚ç‚È‚¢)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(1.0f, 0.7f, -0.7f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.m_diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_scene);

	mInputSystem = new InputSystem();
	mInputSystem->Initialize();

	/*mEmissiveTexture = RENDERER->GetTexture("Assets/title.png");
	mTexture->SetLuminace(1.0f);*/
	//mSprite->SetTexture(mTexture, mEmissiveTexture);

	mSprite = new Sprite("Assets/title.png");

	mNextSceneCount = 0;
}

TitleScene::~TitleScene()
{
	delete mSprite;
	/*RENDERER->DeleteInstance();*/
	/*GAME_OBJECT_MANAGER->RemoveGameObject();*/
}

SceneBase* TitleScene::update()
{
	mInputSystem->PrepareForUpdate();
	mInputSystem->Update();

	const InputState& sceneState = mInputSystem->GetState();


	//if (sceneState.Keyboard.GetKeyState(SDL_SCANCODE_E) == Released)
	//{
	//	/*return new Tutorial(tutorial);*/
	//	/*return new Stage01Scene(stage01);*/
	//	return new Stage02Scene(stage02);
	//}

	if (sceneState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_START) == 1 ||
		sceneState.m_keyboard.GetKeyValue(SDL_SCANCODE_SPACE) == 1)
	{
		return new Tutorial(tutorial);
		//return new Stage01Scene(stage01);
		//return new Stage02Scene(stage02);
	}

	return this;
}