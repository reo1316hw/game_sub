#pragma once

// 前方宣言
class EnemyGenerator;
class EnemyObject;
class BossObject;

/// <summary>
/// エネミーの生成
/// </summary>
class CreateEnemys : public Component
{
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
    CreateEnemys(GameObject* _owner);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~CreateEnemys() {};

    /// <summary>
    /// エネミー生成器を生成
    /// </summary>
    /// <param name="_Pos"> 座標 </param>
    /// <param name="_Scale"> 大きさ </param>
    /// <param name="_playerPtr"> プレイヤーのポインタ </param>
    void CreateEnemyGenerator(const Vector3& _Pos, const Vector3& _Scale, PlayerObject* _playerPtr);

    /// <summary>
    /// エネミーを生成
    /// </summary>
    /// <param name="_Scale"> 大きさ </param>
    /// <param name="_GpmeshName"> gpmeshのパス </param>
    /// <param name="_GpskelName"> gpskelのパス </param>
    /// <param name="_ObjectTag"> オブジェクトのタグ </param>
    /// <param name="_playerPtr"> プレイヤーのポインタ </param>
    void CreateEnemyObject(const Vector3& _Scale, const char* _GpmeshName, const char* _GpskelName,
                           const Tag& _ObjectTag, PlayerObject* _playerPtr);

    /// <summary>
    /// ボスを生成
    /// </summary>
    /// <param name="_Pos"> 座標 </param>
    /// <param name="_Scale"> 大きさ </param>
    /// <param name="_GpmeshName"> gpmeshのパス </param>
    /// <param name="_GpskelName"> gpskelのパス </param>
    /// <param name="_ObjectTag"> オブジェクトのタグ </param>
    /// <param name="_playerPtr"> プレイヤーのポインタ </param>
    void CreateBossObject(const Vector3& _Pos, const Vector3& _Scale, const char* _GpmeshName,
                           const char* _GpskelName, const Tag& _ObjectTag, PlayerObject* _playerPtr);

private:

    // 1区画に生成できる数
    const int MNumGeneratableInOneArea;

    // エネミー生成器の動的配列
    std::vector<EnemyGenerator*> mEnemyGeneratorList;
    // エネミーの動的配列
    std::vector<EnemyObject*> mEnemyObjectList;
    // ボスのポインタ
    BossObject* mBossObjectPtr;

public:// ゲッターセッター

    /// <summary>
    /// エネミーの動的配列を取得
    /// </summary>
    /// <returns> エネミーの動的配列 </returns>
    std::vector<EnemyObject*> GetEnemyObjectList() { return mEnemyObjectList; }

    /// <summary>
    /// ボスのポインタを取得
    /// </summary>
    /// <returns> ボスのポインタ </returns>
    BossObject* GetBossObjectPtr() { return mBossObjectPtr; }
};