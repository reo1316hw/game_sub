#pragma once

/// <summary>
/// ボスがダメージを受けた状態(遠くまで飛行して落ちる)
/// </summary>
class BossObjectStateFlyingBackDamage : public BossObjectStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	BossObjectStateFlyingBackDamage(PlayerObject* _playerPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BossObjectStateFlyingBackDamage() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_owner"> ボス(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	/// <returns> ボスの状態 </returns>
	BossState Update(BossObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// ボスの状態が変更して、最初に1回だけ呼び出される関数
	/// </summary>
	/// <param name="_owner"> ボス(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void Enter(BossObject* _owner, const float _DeltaTime)override;

	/// <summary>
    /// ボスの状態が変更して、最後に1回だけ呼び出される関数
    /// </summary>
    /// <param name="_owner"> ボス(親)のポインタ </param>
    /// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void Exit(BossObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// ボス同士の引き離し
	/// </summary>
	/// <param name="_owner"> ボス親)のポインタ </param>
	/// <param name="_DirTargetEnemyVec"> 対象となるエネミーに向いたベクトル </param>
	void Separation(BossObject* _owner, const Vector3& _DirTargetEnemyVec)override;

private:

	// ヒットストップが終わるタイミング
	const int MHitStopEndTiming;
	// ベクトルを短くする値
	const float MVecShortenVelue;
	// 引き離しベクトルの長さ
	const float MSeparationVecLength;
	// アニメーションの再生速度
	const float MPlayRate;
	// ダメージ時の初期速度
	const float MDamageInitSpeed;
	// 減速値
	const float MDecelerationSpeedValue;

	// ヒットストップするか
	bool mIsHitStop;

	// 体力
	int mHitPoint;
	// ヒットストップするフレーム数
	int mHitStopCount;

	// 死亡時の速度
	float mDamageSpeed;
	// 減速度
	float mDecelerationSpeed;

	// 座標
	Vector3 mPosition;
	// 速度
	Vector3 mVelocity;
	// プレイヤーに向いたベクトル
	Vector3 mDirPlayerVec;

	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
	// ボックスの当たり判定を行うコンポーネントクラスのポインタ
	BoxCollider* mBoxColliderPtr;
};