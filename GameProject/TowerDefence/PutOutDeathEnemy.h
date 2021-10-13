#pragma once

/// <summary>
/// 死亡状態のエネミーを配列から出すためのクラス
/// </summary>
class PutOutDeathEnemy
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PutOutDeathEnemy();

	/// <summary>
    /// デストラクタ
    /// </summary>
	~PutOutDeathEnemy() {};

	/// <summary>
	/// 死亡状態のエネミーを配列から出す
	/// </summary>
	/// <param name="_enemyObjectList"> エネミーの動的配列 </param>
	/// <param name="_enemyObjectPtr"> エネミーのポインター </param>
	/// <returns> 更新されたエネミーの動的配列 </returns>
	std::vector<EnemyObject*> PutOut(std::vector<EnemyObject*> _enemyObjectList, EnemyObject* _enemyObjectPtr);

private:

	/// <summary>
	/// 配列の要素を削除
	/// </summary>
	void RemoveEnemyObjectElements();

	// エネミーの動的配列
	std::vector<EnemyObject*> mEnemyObjectList;

	// エネミーのポインタ
	EnemyObject* mEnemyObjectPtr;
};
