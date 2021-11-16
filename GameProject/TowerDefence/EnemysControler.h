#pragma once
#include "Component.h"

// 前方宣言
class EnemyObject;
class EnemyHitPointGauge;
class EnemyHitPointFrame;

/// <summary>
/// エネミーを制御する
/// </summary>
class EnemysControler : public Component
{
public:
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
	/// <param name="_createEnemysPtr"> エネミーたちを生成するクラスのポインタ </param>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	EnemysControler(GameObject* _owner, CreateEnemys* _createEnemysPtr, PlayerObject* _playerPtr);
	
	/// <summary>
    /// デストラクタ
    /// </summary>
	~EnemysControler() {};

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
	void ActiveEnemy(EnemyObject* _enemyObjectPtr);

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
	void InvadeWithinRange(GameObject* _referenceEnemyItr, GameObject* _targetEnemyItr);

	/// <summary>
	/// エネミーたちを倒した数をカウント
	/// </summary>
	/// <param name="_EnemysCount"> エネミーたちの要素を指定するためのカウント変数 </param>
	/// <param name="_EnemysSize"> エネミーたちの数 </param>
	/// <param name="_referenceEnemyItr"> 対象となるエネミーのポインタ </param>
	void EnemysDeathCount(const int& _EnemysCount, const int& _EnemysSize, EnemyObject* _referenceEnemyItr);

	// 1フレーム前のhp動的配列	
	std::vector<int> mPreHpList;

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
	// 体力が0になり更新しなくなったオブジェクトの数
	int mDeadCount;
	// チュートリアルエネミーを倒した数
	int mTutorialEnemyDeadCount;

	// エネミーたちを生成するクラスのポインタ
	CreateEnemys* mCreateEnemysPtr;
	// エネミーのhpゲージのポインタ
	EnemyHitPointGauge* mEnemyHitPointGaugePtr;
	// エネミーのhpの枠のポインタ
	EnemyHitPointFrame* mEnemyHitPointFramePtr;

public:// ゲッターセッター

	/// <summary>
	/// 体力が0になり更新しなくなったオブジェクトの数を取得
	/// </summary>
	/// <returns> 体力が0になり更新しなくなったオブジェクトの数 </returns>
	int GetDeadCount() { return mDeadCount; }
};