#include "GameObjectManager.h"
#include "GameObject.h"
#include "InputSystem.h"
#include "Renderer.h"
#include "MainCameraObject.h"
#include "SceneBase.h"

GameObjectManager* GameObjectManager::manager = nullptr;

/*
@fn �C���X�^���X�𐶐�
*/
void GameObjectManager::CreateInstance()
{
	if (manager == nullptr)
	{
		manager = new GameObjectManager();
		GameObject::CreateMainCamera();
	}
}

/*
@fn �C���X�^���X���폜
*/
void GameObjectManager::DeleteInstance()
{
	if (manager != nullptr)
	{
		delete manager;
		manager = nullptr;
	}
}

/*
@brief  �Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g����
*/
void GameObjectManager::UpdateGameObject(float _deltaTime)
{

	updatingGameObject = true;

	// �J�������X�V����
	for (auto cameraObject : cameraObjects)
	{
		cameraObject->Update(_deltaTime);
	}

	// �`���[�g���A�����X�V����
	for (auto tutorialObject : tutorialObjects)
	{
		tutorialObject->Update(_deltaTime);
	}

	// �X�e�[�W�P���X�V����
	for (auto stage01Object : stage1Objects)
	{
		stage01Object->Update(_deltaTime);
	}

	// �X�e�[�W�Q���X�V����
	for (auto stage02Object : stage2Objects)
	{
		stage02Object->Update(_deltaTime);
	}

	updatingGameObject = false;

	//�ҋ@���̃I�u�W�F�N�g���X�V���I�u�W�F�N�g�ɒǉ�
	for (auto pending : pendingGameObjects)
	{
		pending->ComputeWorldTransform();
		if (pending->GetScene() == SceneBase::Scene::tutorial)
		{
			tutorialObjects.emplace_back(pending);
		}
		if (pending->GetScene() == SceneBase::Scene::stage01)
		{
			stage1Objects.emplace_back(pending);
		}
		if (pending->GetScene() == SceneBase::Scene::stage02)
		{
			stage2Objects.emplace_back(pending);
		}
	}
	pendingGameObjects.clear();

	/*std::vector<class GameObject*>deadObjs;
	for (auto itr : tutorialObjects)
	{
		if (itr->GetState() == State::Dead)
		{
			deadObjs.emplace_back(itr);
		}
	}

	while (!deadObjs.empty())
	{
		deadObjs.pop_back();
	}
	deadObjs.clear();*/

}
/*
@brief  �Q�[���I�u�W�F�N�g�̓��͏���
*/
void GameObjectManager::ProcessInput(const InputState& _state)
{
	updatingGameObject = true;

	/*for (auto playerObject : playerObjects)
	{
		playerObject->ProcessInput(_state);
	}*/

	for (auto cameraObject : cameraObjects)
	{
		cameraObject->ProcessInput(_state);
	}

	for (auto tutorialObject : tutorialObjects)
	{
		tutorialObject->ProcessInput(_state);
	}

	for (auto stage01Object : stage1Objects)
	{
		stage01Object->ProcessInput(_state);
	}

	for (auto stage02Object : stage2Objects)
	{
		stage02Object->ProcessInput(_state);
	}


	updatingGameObject = false;
}

/*
@brief  �Q�[���I�u�W�F�N�g�̒ǉ�
@param	�ǉ�����GameObject�N���X�̃|�C���^
*/
void GameObjectManager::AddGameObject(GameObject* _object)
{
	if (updatingGameObject)
	{
		pendingGameObjects.emplace_back(_object);
	}
	else
	{

		/*gameObjects.emplace_back(_object);*/

		switch (_object->GetTag())
		{
		case Camera:
			cameraObjects.emplace_back(_object);
			break;
		}

		switch (_object->GetScene())
		{
		case SceneBase::tutorial:
			tutorialObjects.emplace_back(_object);
			break;
		case SceneBase::stage01:
			stage1Objects.emplace_back(_object);
			break;
		case SceneBase::stage02:
			stage2Objects.emplace_back(_object);
			break;
		}
	}
}

/*
@brief  �Q�[���I�u�W�F�N�g�̍폜
@param	�폜����GameObject�N���X�̃|�C���^
*/
void GameObjectManager::RemoveGameObject(GameObject * _object)
{
	auto iter = std::find(pendingGameObjects.begin(), pendingGameObjects.end(), _object);
	if (iter != pendingGameObjects.end())
	{
		std::iter_swap(iter, pendingGameObjects.end() - 1);
		pendingGameObjects.pop_back();
	}

	iter = std::find(tutorialObjects.begin(), tutorialObjects.end(), _object);
	if (iter != tutorialObjects.end())
	{
		std::iter_swap(iter, tutorialObjects.end() - 1);
		tutorialObjects.pop_back();
	}

	iter = std::find(stage1Objects.begin(), stage1Objects.end(), _object);
	if (iter != stage1Objects.end())
	{
		std::iter_swap(iter, stage1Objects.end() - 1);
		stage1Objects.pop_back();
	}

	iter = std::find(stage2Objects.begin(), stage2Objects.end(), _object);
	if (iter != stage2Objects.end())
	{
		std::iter_swap(iter, stage2Objects.end() - 1);
		stage2Objects.pop_back();
	}


}

void GameObjectManager::RemoveGameObjects(SceneBase::Scene _scene)
{
	switch (_scene)
	{
	case SceneBase::tutorial:

		while (!tutorialObjects.empty())
		{
			delete tutorialObjects.back();
		}
		break;

	case SceneBase::stage01:

		while (!stage1Objects.empty())
		{
			delete stage1Objects.back();
		}
		break;

	case SceneBase::stage02:
		while (!stage2Objects.empty())
		{
			delete stage2Objects.back();
		}
		break;
	}
}

/*
@brief �g�p�������ׂẴQ�[���I�u�W�F�N�g���������
@detail �V�[���J�ڂ̍ۂɎg�p�����BGameObject���̍ė��p�t���O�������Ă���I�u�W�F�N�g�͉�����Ȃ�
*/
void GameObjectManager::RemoveAllUsedGameObject()
{
	std::vector<GameObject*> reUseObjects;

	//while (!gameObjects.empty())
	//{
	//	GameObject* obj = gameObjects.back();
	//	if (obj->GetReUseGameObject())
	//	{
	//		reUseObjects.push_back(obj);
	//		gameObjects.pop_back();
	//		continue;
	//	}
	//	delete obj;
	//}

	while (!cameraObjects.empty())
	{
		GameObject* obj = cameraObjects.back();
		if (obj->GetReUseGameObject())
		{
			reUseObjects.push_back(obj);
			cameraObjects.pop_back();
			continue;
		}
		delete obj;
	}

	while (!groundObjects.empty())
	{
		GameObject* obj = groundObjects.back();
		if (obj->GetReUseGameObject())
		{
			reUseObjects.push_back(obj);
			groundObjects.pop_back();
			continue;
		}
		delete obj;
	}

	while (!glassObjects.empty())
	{
		GameObject* obj = glassObjects.back();
		if (obj->GetReUseGameObject())
		{
			reUseObjects.push_back(obj);
			glassObjects.pop_back();
			continue;
		}
		delete obj;
	}

	while (!blockObjects.empty())
	{
		GameObject* obj = blockObjects.back();
		if (obj->GetReUseGameObject())
		{
			reUseObjects.push_back(obj);
			blockObjects.pop_back();
			continue;
		}
		delete obj;
	}

	while (!verticalMoveGroundObjects.empty())
	{
		GameObject* obj = verticalMoveGroundObjects.back();
		if (obj->GetReUseGameObject())
		{
			reUseObjects.push_back(obj);
			verticalMoveGroundObjects.pop_back();
			continue;
		}
		delete obj;
	}

	while (!jumpObjects.empty())
	{
		GameObject* obj = jumpObjects.back();
		if (obj->GetReUseGameObject())
		{
			reUseObjects.push_back(obj);
			jumpObjects.pop_back();
			continue;
		}
		delete obj;
	}

	while (!lateralMoveGroundObjects.empty())
	{
		GameObject* obj = lateralMoveGroundObjects.back();
		if (obj->GetReUseGameObject())
		{
			reUseObjects.push_back(obj);
			lateralMoveGroundObjects.pop_back();
			continue;
		}
		delete obj;
	}

	while (!playerObjects.empty())
	{
		GameObject* obj = playerObjects.back();
		if (obj->GetReUseGameObject())
		{
			reUseObjects.push_back(obj);
			playerObjects.pop_back();
			continue;
		}
		delete obj;
	}

	while (!upBlockObjects.empty())
	{
		GameObject* obj = upBlockObjects.back();
		if (obj->GetReUseGameObject())
		{
			reUseObjects.push_back(obj);
			upBlockObjects.pop_back();
			continue;
		}
		delete obj;
	}

	while (!upBlock_02Objects.empty())
	{
		GameObject* obj = upBlock_02Objects.back();
		if (obj->GetReUseGameObject())
		{
			reUseObjects.push_back(obj);
			upBlock_02Objects.pop_back();
			continue;
		}
		delete obj;
	}

	while (!verticalBlockObjects.empty())
	{
		GameObject* obj = verticalBlockObjects.back();
		if (obj->GetReUseGameObject())
		{
			reUseObjects.push_back(obj);
			verticalBlockObjects.pop_back();
			continue;
		}
		delete obj;
	}

	while (!aerialBlockObjects.empty())
	{
		GameObject* obj = aerialBlockObjects.back();
		if (obj->GetReUseGameObject())
		{
			reUseObjects.push_back(obj);
			aerialBlockObjects.pop_back();
			continue;
		}
		delete obj;
	}

	while (!rightBlockObjects.empty())
	{
		GameObject* obj = rightBlockObjects.back();
		if (obj->GetReUseGameObject())
		{
			reUseObjects.push_back(obj);
			rightBlockObjects.pop_back();
			continue;
		}
		delete obj;
	}

	while (!leftBlockObjects.empty())
	{
		GameObject* obj = leftBlockObjects.back();
		if (obj->GetReUseGameObject())
		{
			reUseObjects.push_back(obj);
			leftBlockObjects.pop_back();
			continue;
		}
		delete obj;
	}

	while (!rightOneBlockObjects.empty())
	{
		GameObject* obj = rightOneBlockObjects.back();
		if (obj->GetReUseGameObject())
		{
			reUseObjects.push_back(obj);
			rightOneBlockObjects.pop_back();
			continue;
		}
		delete obj;
	}

	while (!rightOneBlock_02Objects.empty())
	{
		GameObject* obj = rightOneBlock_02Objects.back();
		if (obj->GetReUseGameObject())
		{
			reUseObjects.push_back(obj);
			rightOneBlock_02Objects.pop_back();
			continue;
		}
		delete obj;
	}

	while (!leftOneBlockObjects.empty())
	{
		GameObject* obj = leftOneBlockObjects.back();
		if (obj->GetReUseGameObject())
		{
			reUseObjects.push_back(obj);
			leftOneBlockObjects.pop_back();
			continue;
		}
		delete obj;
	}

	while (!leftOneBlock_02Objects.empty())
	{
		GameObject* obj = leftOneBlock_02Objects.back();
		if (obj->GetReUseGameObject())
		{
			reUseObjects.push_back(obj);
			leftOneBlock_02Objects.pop_back();
			continue;
		}
		delete obj;
	}

	while (!downBlockObjects.empty())
	{
		GameObject* obj = downBlockObjects.back();
		if (obj->GetReUseGameObject())
		{
			reUseObjects.push_back(obj);
			downBlockObjects.pop_back();
			continue;
		}
		delete obj;
	}

	/*cameraObjects = reUseObjects;
	groundObjects = reUseObjects;
	glassObjects = reUseObjects;
	blockObjects = reUseObjects;
	verticalMoveGroundObjects = reUseObjects;
	jumpObjects = reUseObjects;
	lateralMoveGroundObjects = reUseObjects;
	upBlockObjects = reUseObjects;
	upBlock_02Objects = reUseObjects;
	verticalBlockObjects = reUseObjects;
	aerialBlockObjects = reUseObjects;
	rightBlockObjects = reUseObjects;
	leftBlockObjects = reUseObjects;
	rightOneBlockObjects = reUseObjects;
	rightOneBlock_02Objects = reUseObjects;
	leftOneBlockObjects = reUseObjects;
	leftOneBlock_02Objects = reUseObjects;
	downBlockObjects = reUseObjects;*/
}

GameObject * GameObjectManager::FindGameObject(Tag _tag)
{
	for (auto itr : gameObjects)
	{
		if (itr->GetTag() == _tag)
		{
			return itr;
		}
	}

	return nullptr;
}


std::vector<GameObject*> GameObjectManager::FindGameObjects(Tag _tag)
{
	std::vector<GameObject*> ret;
	for (auto itr : gameObjects)
	{
		if (itr->GetTag() == _tag)
		{
			ret.push_back(itr);
		}
	}
	return ret;
}


GameObjectManager::GameObjectManager()
	: updatingGameObject(false)
{
}


GameObjectManager::~GameObjectManager()
{
	while (!gameObjects.empty())
	{
		delete gameObjects.back();
	}
}