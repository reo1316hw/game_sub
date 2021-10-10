#pragma once

// 前方宣言
class EnemyGenerator;
class EnemyObject;

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

    void UpdateGameObject(float _deltaTime)override;

private:

    void RemoveEnemyObjectElements();

    // 生成タイミング
    const int MCreateTiming;

    // 生成を行うまでのカウント
    int mUntilCreateCount;
    // 生成した回数
    int mCreateCount;

    // エネミーのポインタ
    EnemyObject* mEnemyObject;

    // エネミー生成器プール
    std::vector<EnemyGenerator*> mEnemyGeneratorPools;
    // エネミープール
    std::vector<EnemyObject*> mEnemyObjectPools;
};