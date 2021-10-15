#pragma once

/// <summary>
/// ダメージ受けた状態
/// </summary>
class EnemyObjectStateDamage : public EnemyObjectStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	EnemyObjectStateDamage(PlayerObject* _playerPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyObjectStateDamage() {};

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

private:

	// ダメージ時の速度
	const float MDamageSpeed;
	// ベクトルを短くする値
	const float MVecShortenVelue;
	// 引き離しベクトルの長さ
	const float MSeparationVecLength;

	// このステートに入ってからの経過時刻
	float mElapseTime;
	// アニメーション総時間
	float mTotalAnimTime;

	// 座標
	Vector3 mPosition;
	// 速度
	Vector3 mVelocity;
	// プレイヤーに向いたベクトル
	Vector3 mDirPlayerVec;

	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
};