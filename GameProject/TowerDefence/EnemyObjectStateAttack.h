#pragma once

/// <summary>
/// エネミーの攻撃状態
/// </summary>
class EnemyObjectStateAttack : public EnemyObjectStateBase
{
public:
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_enemyAttackPtr"> エネミーの攻撃判定オブジェクトのポインタ </param>
	EnemyObjectStateAttack(EnemyAttackDecisionObject* _enemyAttackPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyObjectStateAttack() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_owner"> エネミー(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	/// <returns> エネミーの状態 </returns>
	EnemyState Update(EnemyObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// エネミーの状態が変更して、最初に1回だけ呼び出される関数
	/// </summary>
	/// <param name="_owner"> エネミー(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void Enter(EnemyObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// エネミーの状態が変更して、最後に1回だけ呼び出される関数
	/// </summary>
	/// <param name="_owner"> エネミー(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void Exit(EnemyObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// エネミー同士の引き離し
	/// </summary>
	/// <param name="_owner"> エネミー(親)のポインタ </param>
	/// <param name="_DirTargetEnemyVec"> 対象となるエネミーに向いたベクトル </param>
	void Separation(EnemyObject* _owner, const Vector3& _DirTargetEnemyVec)override;

	/// <summary>
	/// ヒットした時の処理
	/// </summary>
	/// <param name="_owner"> エネミー(親)のポインタ </param>
	/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
	void OnCollision(EnemyObject* _owner, const GameObject& _HitObject)override;

private:

	// 当たり判定を有効にするタイミング
	const int MBoxEnableTiming;
	// 状態遷移確率
	const int MStateTransitionProbability;
	// 攻撃時の速度
	const float MAttackSpeed;
	// アニメーションの再生速度
	const float MPlayRate;
	// ベクトルを短くする値
	const float MVecShortenVelue;
	// 引き離しベクトルの長さ
	const float MSeparationVecLength;

	// ダメージを受けたか
	bool mIsDamage;

	// 当たり判定するまでのカウント
	int mHitUntilCount;

	// このステートに入ってからの経過時刻
	float mElapseTime;
	// アニメーション総時間
	float mTotalAnimTime;

	// 座標
	Vector3 mPosition;
	// 速度
	Vector3 mVelocity;
	// 前方ベクトル
	Vector3 mForwardVec;

	// 親の矩形当たり判定を行うクラスのポインタ
	BoxCollider* mOwnerBoxCollider;
};