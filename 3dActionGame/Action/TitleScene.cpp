#include "TitleScene.h"
#include "Tutorial.h"
#include "Renderer.h"
#include "GameObject.h"
#include "InputSystem.h"
#include "Sprite.h"

TitleScene::TitleScene(const Scene& _scene)
{
	// ���C�g��ݒ�(�ݒ肵�Ȃ��Ɖ����f��Ȃ�)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(1.0f, 0.7f, -0.7f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_scene);
	/*GameObject::CreateMainCamera();*/

	/*
	�e�X�g���f���̐����@����͂��̃I�u�W�F�N�g�̌p�����������ŃI�u�W�F�N�g�S�̂��Ǘ����Ă���N���X�ɒǉ����ꂻ�̃N���X�ōs����
	�@TestObject�����������
	�A���N���X����GameObjectManager���̃R���e�i�ɒǉ������
	�BGameObjectManager���������鎞�ɑS�ẴQ�[���I�u�W�F�N�g����������
	*/

	inputSystem = new InputSystem();
	inputSystem->Initialize();
	
	/*mEmissiveTexture = RENDERER->GetTexture("Assets/title.png");
	mTexture->SetLuminace(1.0f);*/
	//sprite->SetTexture(mTexture, mEmissiveTexture);

	sprite = new Sprite("Assets/title.png");

	count = 0;
}

TitleScene::~TitleScene()
{
	delete sprite;
	/*RENDERER->DeleteInstance();*/
	/*GAME_OBJECT_MANAGER->RemoveGameObject();*/
}

SceneBase* TitleScene::update()
{
	//inputSystem->PrepareForUpdate();
	//inputSystem->Update();

	const InputState& sceneState = inputSystem->GetState();
	
	//if (sceneState.Keyboard.GetKeyState(SDL_SCANCODE_E) == Released)
	//{
	//	/*return new Tutorial(tutorial);*/
	//	/*return new Stage01Scene(stage01);*/da
	//	return new Stage02Scene(stage02);
	//}

	if (sceneState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_START) == 1 ||
		sceneState.Keyboard.GetKeyValue(SDL_SCANCODE_SPACE) == 1)
	{
 		return new Tutorial(tutorial);
		//return new Stage01Scene(stage01);
		//return new Stage02Scene(stage02);
	}

	return this;
}

void TitleScene::draw()
{
	RENDERER->Draw();
}