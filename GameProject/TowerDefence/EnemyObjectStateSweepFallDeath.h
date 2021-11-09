#pragma once

class EnemyObjectStateSweepFallDeath : public EnemyObjectStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	EnemyObjectStateSweepFallDeath(PlayerObject* _playerPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyObjectStateSweepFallDeath() {};

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

private:

	// ダメージ時の速度
	const float MDamageSpeed;
	// ベクトルを短くする値
	const float MVecShortenVelue;
	// 引き離しベクトルの長さ
	const float MSeparationVecLength;

	// 体力
	int mHitPoint;

	// このステートに入ってからの経過時刻
	float mElapseTime;
	// アニメーション総時間
	float mTotalAnimTime;

	// 座標
	Vector3 mPosition;
	// 初期座標
	Vector3 mInitPosition;
	// 速度
	Vector3 mVelocity;
	// プレイヤーに向いたベクトル
	Vector3 mDirPlayerVec;

	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
	// エネミーのhpゲージのポインタ
	EnemyHitPointGauge* mEnemyHitPointGaugePtr;
	// エネミーのhpの枠のポインタ
	EnemyHitPointFrame* mEnemyHitPointFramePtr;
	// ボックスの当たり判定を行うコンポーネントクラスのポインタ
	BoxCollider* mBoxColliderPtr;
};