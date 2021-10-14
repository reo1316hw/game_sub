#include "pch.h"

GameObjectManager* GameObjectManager::mManager = nullptr;

/*
@fn インスタンスを生成
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
@fn インスタンスを削除
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
@brief  ゲームオブジェクトのアップデート処理
*/
void GameObjectManager::UpdateGameObject(float _deltaTime)
{
	mUpdatingGameObject = true;

	// カメラを更新する
	for (auto cameraObject : mCameraObjects)
	{
		cameraObject->Update(_deltaTime);
	}

	// 1マップ目を更新する
	for (auto tutorialObject : mGameObjects)
	{
		tutorialObject->Update(_deltaTime);
	}

	mUpdatingGameObject = false;

	//待機中のオブジェクトを更新中オブジェクトに追加
	for (auto pending : mPendingGameObjects)
	{
		pending->ComputeWorldTransform();
		mGameObjects.emplace_back(pending);
	}
	mPendingGameObjects.clear();
}
/*
@brief  ゲームオブジェクトの入力処理
*/
void GameObjectManager::ProcessInput(const InputState& _state)
{
	mUpdatingGameObject = true;

	//カメラ
	for (auto cameraObject : mCameraObjects)
	{
		cameraObject->ProcessInput(_state);
	}
	//1マップ目
	for (auto tutorialObject : mGameObjects)
	{
		tutorialObject->ProcessInput(_state);
	}

	mUpdatingGameObject = false;
}

/*
@brief  ゲームオブジェクトの追加
@param	追加するGameObjectクラスのポインタ
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
@brief  ゲームオブジェクトの削除
@param	削除するGameObjectクラスのポインタ
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
@brief 使用したすべてのゲームオブジェクトを解放する
@detail シーン遷移の際に使用される。GameObject内の再利用フラグが建っているオブジェクトは解放しない
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