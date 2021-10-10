#include "pch.h"

bool	Tutorial::mSendContinueTutorialFlag = false;

Tutorial::Tutorial(const Scene& _scene)
{
	// ƒ‰ƒCƒg‚ðÝ’è(Ý’è‚µ‚È‚¢‚Æ‰½‚à‰f‚ç‚È‚¢)
	RENDERER->SetAmbientLight(Vector3(0.8f, 0.8f, 0.8f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(0.0f, 0.0f, 1.0f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.m_diffuseColor = Vector3(0.36f, 0.44f, 0.5f);
	dir.m_specColor = Vector3(0.4f, 0.4f, 0.4f);

	SetScene(_scene);

    mMapCreate = new MapCreate();
	mMapCreate->OpenFile();
}

Tutorial::~Tutorial()
{
	//GAME_OBJECT_MANAGER->RemoveGameObjects(tutorial);
	delete mMapCreate;
	/*GAME_OBJECT_MANAGER->RemoveGameObject();*/
}

SceneBase* Tutorial::Update(const InputState& _KeyState)
{
	if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_0) == Released)
	{
		PHYSICS->ToggleDebugMode();
	}

	return this;
}
