#pragma once

// 前方宣言
class EnemyGenerator;
class SearchAllEnemy;
class InsertNewEnemy;
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
    ~EnemyObjectManager();
    
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

    // 配列の要素を入れるタイミング
    const int MInElementsTiming;

    // 配列の要素を入れるまでのカウント
    int mUntilInElementsCount;

    // 基準となるエネミーをエネミー配列から検索するクラスのポインタ
    SearchAllEnemy* mSearchAllEnemyPtr;
    // 新しく生成するエネミーを配列に入れるクラスのポインタ
    InsertNewEnemy* mInsertNewEnemyPtr;
    // エネミーのポインタ
    EnemyObject* mEnemyObjectPtr;

    // エネミー生成器の動的配列
    std::vector<EnemyGenerator*> mEnemyGeneratorList;
    // エネミーの動的配列
    std::vector<EnemyObject*> mEnemyObjectList;
};