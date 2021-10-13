#pragma once

/// <summary>
/// 新しく生成するエネミーを配列に入れる
/// </summary>
class InsertNewEnemy
{
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    InsertNewEnemy();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~InsertNewEnemy() {};

    /// <summary>
    /// 配列に入れる処理
    /// </summary>
    /// <param name="_enemyObjectList"> エネミーの動的配列 </param>
    /// <param name="_enemyGeneratorList">　エネミー生成器の動的配列　</param>
    /// <returns> 更新されたエネミーの動的配列 </returns>
    std::vector<EnemyObject*> Insert(std::vector<EnemyObject*> _enemyObjectList, std::vector<EnemyGenerator*> _enemyGeneratorList);

private:

    // エネミーが存在できる数の上限
    const unsigned int MMaxNumEnemysExist;
};