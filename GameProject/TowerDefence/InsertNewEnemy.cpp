#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
InsertNewEnemy::InsertNewEnemy()
	: MMaxNumEnemysExist(1)
{
}

/// <summary>
/// 配列に入れる処理
/// </summary>
/// <param name="_enemyObjectList"> エネミーの動的配列 </param>
/// <param name="_enemyGeneratorList">　エネミー生成器の動的配列　</param>
/// <returns> 更新されたエネミーの動的配列 </returns>
std::vector<EnemyObject*> InsertNewEnemy::Insert(std::vector<EnemyObject*> _enemyObjectList, std::vector<EnemyGenerator*> _enemyGeneratorList)
{
	if (_enemyObjectList.size() < MMaxNumEnemysExist)
	{
		for (auto itr : _enemyGeneratorList)
		{
			// エネミーを生成
			EnemyObject* enemyObjectPtr = itr->CreateEnemyObject();
			_enemyObjectList.push_back(enemyObjectPtr);
		}
	}

	return _enemyObjectList;
}