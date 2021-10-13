#include "pch.h"

SearchReferenceEnemy::SearchReferenceEnemy()
	: mPutOutDeathEnemyPtr(nullptr)
{
	mPutOutDeathEnemyPtr = new PutOutDeathEnemy();
}

SearchReferenceEnemy::~SearchReferenceEnemy()
{
	delete mPutOutDeathEnemyPtr;
}

/// <summary>
/// 基準となるエネミーを検索
/// </summary>
/// <param name="_enemyList"> エネミーの動的配列 </param>
std::vector<EnemyObject*> SearchReferenceEnemy::Search(std::vector<EnemyObject*> _enemyList)
{
	for (auto itr : _enemyList)
	{
		// 死亡状態のエネミーを配列から出す
		/*_enemyList = */mPutOutDeathEnemyPtr->PutOut(_enemyList, itr);

		Vector3 position = itr->GetPosition();

		for (auto otherItr : _enemyList)
		{
			if (otherItr == itr)
			{
				continue;
			}

			Vector3 otherPosition = otherItr->GetPosition();

			Vector3 dis = otherPosition - position;

			if (dis.LengthSq() <= 5000.0f)
			{
				dis.Normalize();
				itr->Separation(dis);
			}
		}
	}

	return _enemyList;

	//if (mEnemyObjectList.size() < MMaxNumEnemysExist)
	//{
	//	for (auto itr : mEnemyGeneratorList)
	//	{
	//		// エネミーを生成
	//		mEnemyObject = itr->CreateEnemyObject();
	//		mEnemyObjectList.push_back(mEnemyObject);
	//	}
	//}
}