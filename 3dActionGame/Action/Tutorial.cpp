#include "Tutorial.h"
#include "Renderer.h"
#include "GameObjectManager.h"
#include "EffectManager.h"
#include "Sprite.h"

bool	Tutorial::sendContinueTutorialFlag = false;

Tutorial::Tutorial(const Scene& _scene)
{
	// ライトを設定(設定しないと何も映らない)
	RENDERER->SetAmbientLight(Vector3(0.8f, 0.8f, 0.8f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(0.0f, 0.0f, 1.0f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.diffuseColor = Vector3(0.36f, 0.44f, 0.5f);
	dir.specColor = Vector3(0.4f, 0.4f, 0.4f);

	SetScene(_scene);
	/*GameObject::CreateMainCamera();*/

	/*
	テストモデルの生成　解放はこのオブジェクトの継承元が自動でオブジェクト全体を管理しているクラスに追加されそのクラスで行われる
	①TestObjectが生成される
	②基底クラス内でGameObjectManager内のコンテナに追加される
	③GameObjectManagerが解放される時に全てのゲームオブジェクトが解放される
	*/

	//sprite = new Sprite("Assets/forest.png");

	mapCreate = new MapCreate();
	if (!mapCreate->OpenFile())
	{
		mapCreate->CreateGround();
		mapCreate->CreateWall();
		mapCreate->CreatePlayer();
		//mapCreate->CreateEnemy();
	}

	count = 0;
}

Tutorial::~Tutorial()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(tutorial);
	/*delete heartUI;*/
	delete sprite;
	delete mapCreate;
	/*GAME_OBJECT_MANAGER->RemoveGameObject();*/
}

SceneBase* Tutorial::update()
{
	return this;
}

void Tutorial::draw()
{
	RENDERER->Draw();
}