#include "Tutorial.h"
#include "Renderer.h"
#include "GameObjectManager.h"
#include "EffectManager.h"
#include "Sprite.h"

bool	Tutorial::sendContinueTutorialFlag = false;

Tutorial::Tutorial(const Scene& _scene)
{
	// ���C�g��ݒ�(�ݒ肵�Ȃ��Ɖ����f��Ȃ�)
	RENDERER->SetAmbientLight(Vector3(0.8f, 0.8f, 0.8f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(0.0f, 0.0f, 1.0f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.diffuseColor = Vector3(0.36f, 0.44f, 0.5f);
	dir.specColor = Vector3(0.4f, 0.4f, 0.4f);

	SetScene(_scene);
	/*GameObject::CreateMainCamera();*/

	/*
	�e�X�g���f���̐����@����͂��̃I�u�W�F�N�g�̌p�����������ŃI�u�W�F�N�g�S�̂��Ǘ����Ă���N���X�ɒǉ����ꂻ�̃N���X�ōs����
	�@TestObject�����������
	�A���N���X����GameObjectManager���̃R���e�i�ɒǉ������
	�BGameObjectManager���������鎞�ɑS�ẴQ�[���I�u�W�F�N�g����������
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