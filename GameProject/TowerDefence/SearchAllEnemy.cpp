#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
SearchAllEnemy::SearchAllEnemy()
	: MDistanceThreshold(5000.0f)
	, mPutOutDeathEnemyPtr(nullptr)
	, mReferenceEnemyPos(Vector3::Zero)
{
	// 死亡状態のエネミーを配列から出すためのクラスを生成
	mPutOutDeathEnemyPtr = new PutOutDeathEnemy();
}

/// <summary>
/// デストラクタ
/// </summary>
SearchAllEnemy::~SearchAllEnemy()
{
	delete mPutOutDeathEnemyPtr;
}

/// <summary>
/// 基準となるエネミーを検索
/// </summary>
/// <param name="_enemyObjectList"> エネミーの動的配列 </param>
/// <returns> 更新されたエネミーの動的配列 </returns>
std::vector<EnemyObject*> SearchAllEnemy::Search(std::vector<EnemyObject*> _enemyObjectList)
{
	for (auto referenceEnemyItr : _enemyObjectList)
	{
		// 死亡状態のエネミーを配列から出す
		mEnemyObjectList = mPutOutDeathEnemyPtr->PutOut(_enemyObjectList, referenceEnemyItr);
		// 基準となるエネミーの座標
		mReferenceEnemyPos = referenceEnemyItr->GetPosition();
		// 対象となるエネミーを検索
		SearchTargetEnemy(_enemyObjectList, referenceEnemyItr);
	}

	return mEnemyObjectList;
}

/// <summary>
/// 対象となるエネミーを検索
/// </summary>
/// <param name="_enemyObjectList"> エネミーの動的配列 </param>
/// <param name="_referenceEnemyItr"> 基準となるエネミー </param>
void SearchAllEnemy::SearchTargetEnemy(std::vector<EnemyObject*> _enemyObjectList, EnemyObject* _referenceEnemyItr)
{
	for (auto targetEnemyItr : _enemyObjectList)
	{
		if (targetEnemyItr == _referenceEnemyItr)
		{
			continue;
		}
		// 範囲内に侵入してきたか求める
		InvadeWithinRange(_referenceEnemyItr, targetEnemyItr);
	}
}

/// <summary>
/// 範囲内に侵入してきたか求める
/// </summary>
/// <param name="_referenceEnemyItr"> 基準となるエネミー </param>
/// <param name="_targetEnemyItr"> 対象となるエネミー </param>
void SearchAllEnemy::InvadeWithinRange(EnemyObject* _referenceEnemyItr, EnemyObject* _targetEnemyItr)
{
	// 対象となるエネミーの座標
	Vector3 targetEnemyPos = _targetEnemyItr->GetPosition();
	// エネミー同士の距離
	Vector3 distance = targetEnemyPos - mReferenceEnemyPos;

	if (distance.LengthSq() <= MDistanceThreshold)
	{
		distance.Normalize();
		_referenceEnemyItr->Separation(distance);
	}
}