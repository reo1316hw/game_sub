#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_enemyActiveBoxPtr"> エネミーを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
/// <param name="_bossActiveBoxPtr"> ボスを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
EnemyObjectManager::EnemyObjectManager(const Tag& _ObjectTag, DeadObjectActiveBox* _enemyActiveBoxPtr, DeadObjectActiveBox* _bossActiveBoxPtr)
	: GameObject(_ObjectTag)
{
	// エネミーたちを生成するクラスを生成
	mCreateEnemysPtr = new CreateEnemys(this);
	// エネミーを制御するクラスを生成
	mEnemysControlerPtr = new EnemysControler(this, mCreateEnemysPtr, _enemyActiveBoxPtr, _bossActiveBoxPtr);
}