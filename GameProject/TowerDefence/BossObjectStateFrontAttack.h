#pragma once

/// <summary>
/// ボスの前方攻撃状態
/// </summary>
class BossObjectStateFrontAttack : public BossObjectStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	BossObjectStateFrontAttack(PlayerObject* _playerPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BossObjectStateFrontAttack() {};

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
	/// ボス同士の引き離し
	/// </summary>
	/// <param name="_owner"> ボス(親)のポインタ </param>
	/// <param name="_DirTargetEnemyVec"> 対象となるエネミーに向いたベクトル </param>
	void Separation(BossObject* _owner, const Vector3& _DirTargetEnemyVec)override;

	/// <summary>
	/// ヒットした時の処理
	/// </summary>
	/// <param name="_owner"> ボス(親)のポインタ </param>
	/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
	void OnCollision(BossObject* _owner, const GameObject& _HitObject)override;

private:

	// 向きを確定するタイミング
	const int MTimingFixFacing;
	// 状態を変えるための距離
	const float MTransitionStateDistance;
	// ベクトルを短くする値
	const float MVecShortenVelue;
	// 引き離しベクトルの長さ
	const float MSeparationVecLength;

	// ダメージを受けたか
	bool mIsDamage;

	// 向きを確定するまでの時間
	int mFacingFixUntilTime;

	// 座標
	Vector3 mPosition;
	// 速度
	Vector3 mVelocity;

	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
};