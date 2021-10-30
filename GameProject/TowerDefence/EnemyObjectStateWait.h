#pragma once

/// <summary>
/// エネミーの待機状態
/// </summary>
class EnemyObjectStateWait : public EnemyObjectStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	EnemyObjectStateWait(PlayerObject* _playerPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyObjectStateWait() {};

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
	/// プレイヤーの攻撃にヒットした時の処理
	/// </summary>
	/// <param name="_HitTag"> ヒットする相手 </param>
	/// <param name="_DamageValuePlayerAttack"> ダメージ量 </param>
	/// <returns> ヒットしたか </returns>
	bool HitAttack(const Tag& _HitTag, const int& _DamageValuePlayerAttack);

	// ヒットするオブジェクトのリスト
	Tag mHitTagList[4];

	// 遷移するタイミング
	const int MTransitionTimingNum;
	// 状態遷移確率
	const int MStateTransitionProbability;
	// プレイヤーの1段階目の通常攻撃のダメージ値
	const int MDamageValuePlayerFirstAttack;
	// 状態を変えるための距離(近距離)
	const float MTransitionStateShortDistance;
	// 状態を変えるための距離(中距離)
	const float MTransitionStateMediumDistance;
	// ベクトルを短くする値
	const float MVecShortenVelue;
	// 引き離しベクトルの長さ
	const float MSeparationVecLength;

	// ダメージを受けたか
	bool mIsDamage;

	// ダメージ値
	int mDamageValue;
	// 待機する時間のカウント変数
	int mPeriodWaitCount;
	// ヒットする相手のリストの要素数
	int mHitTagListSize;

	// 座標
	Vector3 mPosition;
	// 速度
	Vector3 mVelocity;
	// ヒットしたオブジェクトのタグ
	Tag mHitTag;

	// エネミーのポインタ
	EnemyObject* mEnemyPtr;
	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
};