#pragma once
#include <SDL.h>
#include <unordered_map>
#include <vector>
#include <string>
#include "SceneBase.h"

// 前方宣言
class FPS;
class GameObject;
class InputSystem;

/*
@file Game.h
@brief ゲームの進行を行う
*/
class Game
{
public:
	Game();
	~Game();

	/*
	@brief	初期化処理
	@return true : 成功, false : 失敗
	*/
	bool Initialize();
	/*
	@brief  終了処理
	*/
	void Termination();
	/*
	@brief  ゲームループ
	*/
	void GameLoop();
	// 最初のシーンを決める関数
	void SetFirstScene(SceneBase* _firstScene);

	/*bool GetScene() { return isScene; };

	void SetScene(bool _isScene) { isScene = _isScene; };*/

	//シーンを切り替えるか
	bool mSceneFlag;

	static int mDebug;
private:
	SceneBase* mNowScene;
	/*Stage01Scene* stage01Scene;*/

	/*
	@brief  入力関連の処理
	*/
    void ProcessInput();
	/*
	@brief  描画関連の処理
	*/
    virtual void GenerateOutput();

	/*
	@brief  ゲームの更新処理
	*/
	void UpdateGame();

	/*
	@brief   ロードしたデータの解放
	*/
	void UnloadData();

	// FPS計測クラス
	FPS* mFps;
    // 入力管理クラス
	InputSystem* mInputSystem;
	//ゲームを続けるかどうか
    bool mRunningFlag;
};

