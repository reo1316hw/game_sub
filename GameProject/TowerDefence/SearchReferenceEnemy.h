#pragma once

class PutOutDeathEnemy;

/// <summary>
/// 基準となるエネミーをエネミー配列から検索
/// </summary>
class SearchReferenceEnemy
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SearchReferenceEnemy();
	
	/// <summary>
    /// デストラクタ
    /// </summary>
	~SearchReferenceEnemy();

	/// <summary>
    /// 基準となるエネミーを検索
    /// </summary>
	/// <param name="_enemyList"> エネミーの動的配列 </param>
	std::vector<EnemyObject*> Search(std::vector<EnemyObject*> _enemyList);

private:

	// 死亡状態のエネミーを配列から出すためのクラスのポインタ
	PutOutDeathEnemy* mPutOutDeathEnemyPtr;
};

