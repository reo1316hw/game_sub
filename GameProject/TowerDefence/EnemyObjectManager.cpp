#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
EnemyObjectManager::EnemyObjectManager(const Tag& _ObjectTag, PlayerObject* _playerPtr)
	: GameObject(_ObjectTag)
{
	// エネミーたちを生成するクラスを生成
	mCreateEnemysPtr = new CreateEnemys(this);
	// エネミーを制御するクラスを生成
	mEnemysControlerPtr = new EnemysControler(this, mCreateEnemysPtr, _playerPtr);
}