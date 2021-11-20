#pragma once

/// <summary>
/// エネミーの死亡状態(吹っ飛んで落ちる)
/// </summary>
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

	// ベクトルを短くする値
	const float MVecShortenVelue;
	// 引き離しベクトルの長さ
	const float MSeparationVecLength;
	// 死亡時の初速度
	const float MDeathInitSpeed;
	// 重力
	const float MGravity;

	// 体力
	int mHitPoint;

	// 死亡時の速度
	float mDeathSpeed;

	// 座標
	Vector3 mPosition;
	// 初期座標
	Vector3 mInitPosition;
	// このステートに入った時の座標
	Vector3 mNowStateInitPos;
	// 速度
	Vector3 mVelocity;
	// プレイヤーに向いたベクトル
	Vector3 mDirPlayerVec;

	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
	// エネミーのhpゲージのポインタ
	ParticleGauge* mEnemyHitPointGaugePtr;
	// エネミーのhpの枠のポインタ
	ParticleFrame* mEnemyHitPointFramePtr;
	// ボックスの当たり判定を行うコンポーネントクラスのポインタ
	BoxCollider* mBoxColliderPtr;
};