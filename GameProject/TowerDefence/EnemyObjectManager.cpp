#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
EnemyObjectManager::EnemyObjectManager(const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
{
	// エネミーたちを生成するクラスを生成
	mCreateEnemysPtr = new CreateEnemys(this);
	// エネミーを制御するクラスを生成
	new EnemyControler(this, mCreateEnemysPtr);
}