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

	/// <summary>
	/// 攻撃を受けた時の処理
	/// </summary>
	/// <param name="_HitTag"> ヒットしたオブジェクトのタグ </param>
	/// <param name="_DamageValuePlayerAttack"> ダメージ量 </param>
	/// <returns> ヒットしたか </returns>
	bool ReceivedAttack(const Tag& _HitTag, const int& _DamageValuePlayerAttack);

	// ヒットするオブジェクトのリスト
	Tag mHitTagList[4];

	// ダメージ値のリスト
	int mDamageValueList[4];

	// 状態遷移確率
	const int MStateTransitionProbability;
	// 当たり判定を有効にするタイミング
	const float MBoxEnableTiming;
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
	// 当たり判定の状態
	// true : 有効, false : 無効
	bool mIsCollisionState;
	// 現在のステートに入って1回だけ当たり判定を有効にする
	bool mIsOneCollisionState;

	// ダメージ値
	int mDamageValue;
	// ヒットする相手のリストの要素数
	int mHitTagListSize;

	// このステートに入ってからの経過時刻
	float mElapseTime;
	// アニメーション総時間
	float mTotalAnimTime;
	// 当たり判定を無効にするタイミング
	float mBoxDisableTiming;

	// 座標
	Vector3 mPosition;
	// 速度
	Vector3 mVelocity;
	// 前方ベクトル
	Vector3 mForwardVec;
	// ヒットしたオブジェクトのタグ
	Tag mHitTag;

	// エネミーのポインタ
	EnemyObject* mEnemyPtr;
	// 親の矩形当たり判定を行うクラスのポインタ
	BoxCollider* mOwnerBoxCollider;
};