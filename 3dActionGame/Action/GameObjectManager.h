#pragma once
#define GAME_OBJECT_MANAGER GameObjectManager::GetInstance()

#include "SDL.h"
#include <unordered_map>
#include <vector>
#include <string>
#include "GameObject.h"

class GameObject;
struct InputState;

/*
@file GameObjectManager.h
@brief ゲームオブジェクトの更新を行う
*/
class GameObjectManager
{
public:
	/*
	@return 自身のインスタンスを返す
	*/
	static GameObjectManager* GetInstance() { return mManager; }
	/*
	@fn インスタンスを生成
	*/
	static void CreateInstance();
	/*
	@fn インスタンスを削除
	*/
	static void DeleteInstance();

	/*
	@brief  ゲームオブジェクトのアップデート処理
	*/
	void UpdateGameObject(float _deltaTime);

	/*
	@brief  ゲームオブジェクトの入力処理
	*/
	void ProcessInput(const InputState& _state);

	/*
	@brief  ゲームオブジェクトの追加
	@param	追加するGameObjectクラスのポインタ
	*/
	void AddGameObject(GameObject* _object);

	/*
	@brief  ゲームオブジェクトの削除
	@param	削除するGameObjectクラスのポインタ
	*/
	void RemoveGameObject(GameObject* _object);
	void RemoveGameObjects(SceneBase::Scene _scene);

	/*
	@brief 使用したすべてのゲームオブジェクトを解放する
	@detail シーン遷移の際に使用される。GameObject内の再利用フラグが建っているオブジェクトは解放しない
	*/
	void RemoveAllUsedGameObject();

	GameObject* FindGameObject(Tag _tag);
	std::vector<GameObject*> FindGameObjects(Tag _tag);

private:
	GameObjectManager();
	~GameObjectManager();

	static GameObjectManager* mManager;

	//ゲームオブジェクトのポインタの可変長コンテナ
	//カメラを格納するための可変長コンテナ
	std::vector<GameObject*> mCameraObjects;
	//チュートリアル時の全てのゲームオブジェクトを格納するための可変長コンテナ
	std::vector<GameObject*> mTutorialObjects; 
	//ステージ1の時の全てのゲームオブジェクトを格納するための可変長コンテナ
	std::vector<GameObject*> mStage01Objects;
	//ステージ2の時の全てのゲームオブジェクトを格納するための可変長コンテナ
	std::vector<GameObject*> mStage02Objects;

	//Update中に追加されたゲームオブジェクトのポインタを一時的に保存する可変長コンテナ
	std::vector<GameObject*> mPendingGameObjects;

	//Update中かどうか
	bool mUpdatingGameObject;

};
