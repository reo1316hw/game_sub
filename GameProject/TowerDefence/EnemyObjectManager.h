#pragma once

// 前方宣言
class EnemyGenerator;
class EnemyObject;

/// <summary>
/// エネミーの管理
/// </summary>
class EnemyObjectManager : public GameObject
{
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="_ObjectTag"> タグ </param>
    /// <param name="_SceneTag"> シーンタグ </param>
	EnemyObjectManager(const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~EnemyObjectManager() {};
    
	/// <summary>
	/// エネミー生成器を生成
	/// </summary>
    /// <param name="_Pos"> 座標 </param>
    /// <param name="_Scale"> 大きさ </param>
    /// <param name="_playerPtr"> プレイヤーのポインタ </param>
	void CreateEnemyGenerator(const Vector3& _Pos, const Vector3& _Scale, PlayerObject* _playerPtr);

    /// <summary>
    /// オブジェクトの更新処理
    /// </summary>
    /// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
    void UpdateGameObject(float _deltaTime)override;

private:

    /// <summary>
    /// 死亡状態の要素を配列から出す処理
    /// </summary>
    void PutOutDeathElements();

    /// <summary>
    /// 新たな要素を配列に入れる処理
    /// </summary>
    void InsertNewElements();

    /// <summary>
    /// 配列の要素を削除
    /// </summary>
    /// <param name="_enemyObjectPtr"> エネミーのポインター </param>
    void RemoveEnemyObjectElements(EnemyObject* _enemyObjectPtr);

    // 配列の要素を出し入れするタイミング
    const int MInOutElementsTiming;
    // エネミーが存在できる数の上限
    const int MMaxNumEnemysExist;

    // 配列の要素を出し入れするまでのカウント
    int mUntilInOutElementsCount;

    // エネミーのポインタ
    EnemyObject* mEnemyObject;

    // エネミー生成器の動的配列
    std::vector<EnemyGenerator*> mEnemyGeneratorList;
    // エネミーの動的配列
    std::vector<EnemyObject*> mEnemyObjectList;
};