#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
PutOutDeathEnemy::PutOutDeathEnemy()
	: mEnemyObjectPtr(nullptr)
{
}

/// <summary>
/// 死亡状態のエネミーを配列から出す
/// </summary>
/// <param name="_enemyObjectList"> エネミーの動的配列 </param>
/// <param name="_enemyObjectPtr"> エネミーのポインター </param>
/// <returns> 更新されたエネミーの動的配列 </returns>
std::vector<EnemyObject*> PutOutDeathEnemy::PutOut(std::vector<EnemyObject*> _enemyObjectList, EnemyObject* _enemyObjectPtr)
{
	mEnemyObjectList = _enemyObjectList;
	mEnemyObjectPtr = _enemyObjectPtr;

	if (mEnemyObjectPtr->GetState() == State::eDead)
	{
		// 配列の要素を削除
		RemoveEnemyObjectElements();
	}

	return mEnemyObjectList;
}

/// <summary>
/// 配列の要素を削除
/// </summary>
void PutOutDeathEnemy::RemoveEnemyObjectElements()
{
	auto iter = std::find(mEnemyObjectList.begin(), mEnemyObjectList.end(), mEnemyObjectPtr);
	if (iter != mEnemyObjectList.end())
	{
		std::iter_swap(iter, mEnemyObjectList.end() - 1);
		mEnemyObjectList.pop_back();
	}
}