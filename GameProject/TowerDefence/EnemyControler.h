#pragma once
#include "Component.h"

// 前方宣言
class EnemyObject;

/// <summary>
/// エネミーを制御する
/// </summary>
class EnemyControler : public Component
{
public:
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_enemyObjectManagerPtr"> エネミーマネージャーのポインタ </param>
	/// <param name="_createEnemysPtr"> エネミーたちを生成するクラスのポインタ </param>
	EnemyControler(EnemyObjectManager* _enemyObjectManagerPtr, CreateEnemys* _createEnemysPtr);
	
	/// <summary>
    /// デストラクタ
    /// </summary>
	~EnemyControler() {};

	/// <summary>
    /// フレーム毎の処理
    /// </summary>
    /// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void Update(float _deltaTime)override;

private:

	/// <summary>
	/// 一定時間が経ったら非アクティブなエネミーをアクティブにする
	/// </summary>
	/// <param name="_enemyObjectPtr"> エネミーのポインタ </param>
	/// <returns> 検索を続けるか </returns>
	bool ActiveEnemy(EnemyObject* _enemyObjectPtr);

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

	// 配列の要素を入れるタイミング
	const int MInElementsTiming;
	// 1回にアクティブにできるエネミーの数の上限
	const int MMaxActiveInOnce;
	// 距離のしきい値
	const float MDistanceThreshold;

	// 配列の要素を入れるまでのカウント
	int mUntilInElementsCount;

	// アクティブになったオブジェクトの数
	int mActiveCount;

	// 基準となるエネミーの座標
	Vector3 mReferenceEnemyPos;

	// エネミーたちを生成するクラスのポインタ
	CreateEnemys* mCreateEnemysPtr;
};

