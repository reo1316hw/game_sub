#pragma once

// 前方宣言
class PutOutDeathEnemy;

/// <summary>
/// 全てのエネミーをエネミー配列から検索
/// </summary>
class SearchAllEnemy
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SearchAllEnemy();
	
	/// <summary>
    /// デストラクタ
    /// </summary>
	~SearchAllEnemy();

	/// <summary>
    /// 全てのエネミーを検索
    /// </summary>
	/// <param name="_enemyObjectList"> エネミーの動的配列 </param>
	/// <returns> 更新されたエネミーの動的配列 </returns>
	std::vector<EnemyObject*> Search(std::vector<EnemyObject*> _enemyObjectList);

private:

	/// <summary>
	/// 対象となるエネミーを検索
	/// </summary>
	/// <param name="_enemyObjectList"> エネミーの動的配列 </param>
	/// <param name="_referenceEnemyItr"> 基準となるエネミー </param>
	void SearchTargetEnemy(std::vector<EnemyObject*> _enemyObjectList, EnemyObject* _referenceEnemyItr);

	/// <summary>
	/// 範囲内に侵入してきたか求める
	/// </summary>
	/// <param name="_referenceEnemyItr"> 基準となるエネミー </param>
	/// <param name="_targetEnemyItr"> 対象となるエネミー </param>
	void InvadeWithinRange(EnemyObject* _referenceEnemyItr, EnemyObject* _targetEnemyItr);

	// 距離のしきい値
	const float MDistanceThreshold;

	// エネミーの動的配列
	std::vector<EnemyObject*> mEnemyObjectList;

	// 基準となるエネミーの座標
	Vector3 mReferenceEnemyPos;

	// 死亡状態のエネミーを配列から出すためのクラスのポインタ
	PutOutDeathEnemy* mPutOutDeathEnemyPtr;
};

