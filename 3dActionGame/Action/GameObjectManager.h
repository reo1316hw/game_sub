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
	static GameObjectManager* GetInstance() { return manager; }
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

	static GameObjectManager* manager;

	//ゲームオブジェクトのポインタの可変長コンテナ
	std::vector<GameObject*> gameObjects;
	std::vector<GameObject*> cameraObjects;
	std::vector<GameObject*> groundObjects;
	std::vector<GameObject*> glassObjects;
	std::vector<GameObject*> blockObjects;
	std::vector<GameObject*> verticalMoveGroundObjects;
	std::vector<GameObject*> jumpObjects;
	std::vector<GameObject*> lateralMoveGroundObjects;
	std::vector<GameObject*> playerObjects;
	std::vector<GameObject*> upBlockObjects;
	std::vector<GameObject*> upBlock_02Objects;
	std::vector<GameObject*> verticalBlockObjects;
	std::vector<GameObject*> aerialBlockObjects;
	std::vector<GameObject*> rightBlockObjects;
	std::vector<GameObject*> leftBlockObjects;
	std::vector<GameObject*> rightOneBlockObjects;
	std::vector<GameObject*> rightOneBlock_02Objects;
	std::vector<GameObject*> leftOneBlockObjects;
	std::vector<GameObject*> leftOneBlock_02Objects;
	std::vector<GameObject*> downBlockObjects;
	std::vector<GameObject*> tutorialObjects;
	std::vector<GameObject*> stage1Objects;
	std::vector<GameObject*> stage2Objects;

	//Update中に追加されたゲームオブジェクトのポインタを一時的に保存する可変長コンテナ
	std::vector<GameObject*> pendingGameObjects;

	//Update中かどうか
	bool updatingGameObject;

};
