#pragma once

/// <summary>
/// ボスの死亡状態(吹っ飛んで落ちる)
/// </summary>
class BossObjectStateSweepFallDamage : public BossObjectStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	BossObjectStateSweepFallDamage(PlayerObject* _playerPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BossObjectStateSweepFallDamage() {};

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
	/// <param name="_owner"> ボス親)のポインタ </param>
	/// <param name="_DirTargetEnemyVec"> 対象となるエネミーに向いたベクトル </param>
	void Separation(BossObject* _owner, const Vector3& _DirTargetEnemyVec)override;

	/// <summary>
	/// ヒットした時の処理
	/// </summary>
	/// <param name="_owner"> ボス(親)のポインタ </param>
	/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
	void OnCollision(BossObject* _owner, const GameObject& _HitObject)override;

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

	// ベクトルを短くする値
	const float MVecShortenVelue;
	// 引き離しベクトルの長さ
	const float MSeparationVecLength;
	// ダメージ時の初速度
	const float MDamageInitSpeed;
	// 重力
	const float MGravity;
	// 当たり判定を行わない時間
	const float MNotHitTime;

	// ダメージを受けたか
	bool mIsDamage;

	// 体力
	int mHitPoint;
	// ダメージ値
	int mDamageValue;
	// ヒットする相手のリストの要素数
	int mHitTagListSize;

	// このステートに入ってからの経過時刻
	float mElapseTime;
	// ダメージ時の速度
	float mDamageSpeed;

	// 座標
	Vector3 mPosition;
	// このステートに入った時の座標
	Vector3 mNowStateInitPos;
	// 速度
	Vector3 mVelocity;
	// プレイヤーに向いたベクトル
	Vector3 mDirPlayerVec;

	// ヒットしたオブジェクトのタグ
	Tag mHitTag;

	// ボスのポインタ
	BossObject* mBossPtr;
	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
};