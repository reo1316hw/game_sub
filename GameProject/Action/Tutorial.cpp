#include "Tutorial.h"
#include "Renderer.h"
#include "GameObjectManager.h"
#include "Sprite.h"
#include "MapCreate.h"

bool	Tutorial::mSendContinueTutorialFlag = false;

Tutorial::Tutorial(const Scene& _scene)
{
	// ライトを設定(設定しないと何も映らない)
	RENDERER->SetAmbientLight(Vector3(0.8f, 0.8f, 0.8f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(0.0f, 0.0f, 1.0f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.m_diffuseColor = Vector3(0.36f, 0.44f, 0.5f);
	dir.m_specColor = Vector3(0.4f, 0.4f, 0.4f);

	SetScene(_scene);
	//sprite = new Sprite("Assets/forest.png");

	mMapCreate = new MapCreate();
	if (!mMapCreate->OpenFile())
	{
		mMapCreate->CreateGround();
		mMapCreate->CreateWall();
		mMapCreate->CreatePlayer();
		//mMapCreate->CreateEnemy();
	}
}

Tutorial::~Tutorial()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(tutorial);
	delete mMapCreate;
	/*GAME_OBJECT_MANAGER->RemoveGameObject();*/
}

SceneBase* Tutorial::update()
{
	return this;
}
