#pragma once

// 前方宣言
class CreateEnemys;

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
	EnemyObjectManager(const Tag& _ObjectTag);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~EnemyObjectManager() {};

private:

    // エネミーたちを生成するクラスのポインタ
    CreateEnemys* mCreateEnemysPtr;

public:// ゲッターセッター

    /// <summary>
    /// エネミーたちを生成するクラスのポインタを取得
    /// </summary>
    /// <returns> エネミーたちを生成するクラスのポインタ </returns>
    CreateEnemys* GetCreateEnemysPtr() {return mCreateEnemysPtr; }
};