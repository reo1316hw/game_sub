#include "pch.h"

GameObjectManager* GameObjectManager::mManager = nullptr;

/*
@fn �C���X�^���X�𐶐�
*/
void GameObjectManager::CreateInstance()
{
	if (mManager == nullptr)
	{
		mManager = new GameObjectManager();
		GameObject::CreateMainCamera();
	}
}

/*
@fn �C���X�^���X���폜
*/
void GameObjectManager::DeleteInstance()
{
	if (mManager != nullptr)
	{
		delete mManager;
		mManager = nullptr;
	}
}

/*
@brief  �Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g����
*/
void GameObjectManager::UpdateGameObject(float _deltaTime)
{
	mUpdatingGameObject = true;

	// �J�������X�V����
	for (auto cameraObject : mCameraObjects)
	{
		cameraObject->Update(_deltaTime);
	}

	// 1�}�b�v�ڂ��X�V����
	for (auto tutorialObject : mGameObjects)
	{
		tutorialObject->Update(_deltaTime);
	}

	mUpdatingGameObject = false;

	//�ҋ@���̃I�u�W�F�N�g���X�V���I�u�W�F�N�g�ɒǉ�
	for (auto pending : mPendingGameObjects)
	{
		pending->ComputeWorldTransform();
		mGameObjects.emplace_back(pending);
	}
	mPendingGameObjects.clear();
}
/*
@brief  �Q�[���I�u�W�F�N�g�̓��͏���
*/
void GameObjectManager::ProcessInput(const InputState& _state)
{
	mUpdatingGameObject = true;

	//�J����
	for (auto cameraObject : mCameraObjects)
	{
		cameraObject->ProcessInput(_state);
	}
	//1�}�b�v��
	for (auto tutorialObject : mGameObjects)
	{
		tutorialObject->ProcessInput(_state);
	}

	mUpdatingGameObject = false;
}

/*
@brief  �Q�[���I�u�W�F�N�g�̒ǉ�
@param	�ǉ�����GameObject�N���X�̃|�C���^
*/
void GameObjectManager::AddGameObject(GameObject* _object)
{
	if (mUpdatingGameObject)
	{
		mPendingGameObjects.emplace_back(_object);
	}
	else
	{
		/*switch (_object->GetTag())
		{
		case eCamera:
			mCameraObjects.emplace_back(_object);
			break;
		case !eCamera:
			mGameObjects.emplace_back(_object);
			break;
		}*/

		Tag tag = _object->GetTag();

		if (tag == Tag::eCamera)
		{
			mCameraObjects.emplace_back(_object);
		}
		else
		{
			mGameObjects.emplace_back(_object);
		}
	}
}

/*
@brief  �Q�[���I�u�W�F�N�g�̍폜
@param	�폜����GameObject�N���X�̃|�C���^
*/
void GameObjectManager::RemoveGameObject(GameObject * _object)
{
	auto iter = std::find(mCameraObjects.begin(), mCameraObjects.end(), _object);
	if (iter != mCameraObjects.end())
	{
		std::iter_swap(iter, mCameraObjects.end() - 1);
		mCameraObjects.pop_back();
	}

	iter = std::find(mGameObjects.begin(), mGameObjects.end(), _object);
	if (iter != mGameObjects.end())
	{
		std::iter_swap(iter, mGameObjects.end() - 1);
		mGameObjects.pop_back();
	}
}

/*
@brief �g�p�������ׂẴQ�[���I�u�W�F�N�g���������
@detail �V�[���J�ڂ̍ۂɎg�p�����BGameObject���̍ė��p�t���O�������Ă���I�u�W�F�N�g�͉�����Ȃ�
*/
//void GameObjectManager::RemoveAllUsedGameObject()
//{
//	std::vector<GameObject*> reUseObjects;
//
//	while (!gameObjects.empty())
//	{
//		GameObject* obj = gameObjects.back();
//		if (obj->GetReUseGameObject())
//		{
//			reUseObjects.push_back(obj);
//			gameObjects.pop_back();
//			continue;
//		}
//		delete obj;
//	}
//
//	while (!cameraObjects.empty())
//	{
//		GameObject* obj = cameraObjects.back();
//		if (obj->GetReUseGameObject())
//		{
//			reUseObjects.push_back(obj);
//			cameraObjects.pop_back();
//			continue;
//		}
//		delete obj;
//	}
//}

//GameObject * GameObjectManager::FindGameObject(Tag _tag)
//{
//	for (auto itr : mTutorialObjects)
//	{
//		if (itr->GetTag() == _tag)
//		{
//			return itr;
//		}
//	}
//
//	return nullptr;
//}


//std::vector<GameObject*> GameObjectManager::FindGameObjects(Tag _tag)
//{
//	std::vector<GameObject*> ret;
//	for (auto itr : gameObjects)
//	{
//		if (itr->GetTag() == _tag)
//		{
//			ret.push_back(itr);
//		}
//	}
//	return ret;
//}


GameObjectManager::GameObjectManager()
	: mUpdatingGameObject(false)
{
}


GameObjectManager::~GameObjectManager()
{
	while (!mCameraObjects.empty())
	{
		delete mCameraObjects.back();
	}

	while (!mGameObjects.empty())
	{
		delete mGameObjects.back();
	}
}