#pragma once

// 前方宣言
class CreateEnemys;
class EnemysControler;

/// <summary>
/// エネミーの管理
/// </summary>
class EnemyObjectManager : public GameObject
{
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="_ObjectTag"> オブジェクトのタグ </param>
    /// <param name="_enemyActiveBoxPtr"> エネミーを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
    /// <param name="_bossActiveBoxPtr"> ボスを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
	EnemyObjectManager(const Tag& _ObjectTag, DeadObjectActiveBox* _enemyActiveBoxPtr, DeadObjectActiveBox* _bossActiveBoxPtr);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~EnemyObjectManager() {};

private:

    // エネミーたちを生成するクラスのポインタ
    CreateEnemys* mCreateEnemysPtr;
    // エネミーたちを制御するクラスのポインタ
    EnemysControler* mEnemysControlerPtr;

public:// ゲッターセッター

    /// <summary>
    /// エネミーたちを生成するクラスのポインタを取得
    /// </summary>
    /// <returns> エネミーたちを生成するクラスのポインタ </returns>
    CreateEnemys* GetCreateEnemysPtr() {return mCreateEnemysPtr; }

    /// <summary>
    /// エネミーたちを制御するクラスのポインタを取得
    /// </summary>
    /// <returns> エネミーたちを制御するクラスのポインタ </returns>
    EnemysControler* GetEnemysControlerPtr() { return mEnemysControlerPtr; }
};