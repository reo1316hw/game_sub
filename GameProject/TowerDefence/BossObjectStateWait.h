#pragma once

/// <summary>
/// ボスの待機状態
/// </summary>
class BossObjectStateWait : public BossObjectStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	BossObjectStateWait(PlayerObject* _playerPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BossObjectStateWait() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_owner"> ボス親)のポインタ </param>
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
	/// ボスとエネミーの引き離し
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

	/// <summary>
	/// 攻撃を受けた時の処理
	/// </summary>
	/// <param name="_HitTag"> ヒットしたオブジェクトのタグ </param>
	/// <param name="_DamageValuePlayerAttack"> ダメージ量 </param>
	/// <returns> ヒットしたか </returns>
	bool ReceivedAttack(const Tag& _HitTag, const int& _DamageValuePlayerAttack);

	/// <summary>
	/// ダメージを負う処理
	/// </summary>
	/// <param name="_owner"> ボス(親)のポインタ </param>
	void SufferDamage(BossObject* _owner);

	// ヒットするオブジェクトのリスト
	Tag mHitTagList[4];

	// ダメージ値のリスト
	int mDamageValueList[4];

	// 遷移するタイミング
	const int MTransitionTimingNum;
	// 状態を変えるための距離
	const float MTransitionStateDistance;
	// ベクトルを短くする値
	const float MVecShortenVelue;
	// 引き離しベクトルの長さ
	const float MSeparationVecLength;

	// ダメージを受けたか
	bool mIsDamage;
	// hpが変更されたか
	bool mIsChangeHitPoint;

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
	BossObject* mBossPtr;
	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
};