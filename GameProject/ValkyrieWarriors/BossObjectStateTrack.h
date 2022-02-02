#pragma once

/// <summary>
/// ボスの追跡状態
/// </summary>
class BossObjectStateTrack : public BossObjectStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	BossObjectStateTrack(PlayerObject* _playerPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BossObjectStateTrack() {};

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

	// 頭上攻撃に遷移するタイミング
	const int MTimingTransitionOverheadAttack;
	// 状態を変えるための距離
	const float MTransitionStateDistance;
	// ベクトルを短くする値
	const float MVecShortenVelue;
	// 引き離しベクトルの長さ
	const float MSeparationVecLength;

	// ダメージを受けたか
	bool mIsDamage;
	// ダッシュアタックhpが変更されたか
	bool mDashAttackIsChangeHitPoint;
	// 一回目の通常攻撃hpが変更されたか
	bool mFirstAttackIsChangeHitPoint;

	// ダメージ値
	int mDamageValue;
	// 頭上攻撃に遷移するまでのカウント
	int UntilTransitionOverheadAttackCount;
	// ヒットする相手のリストの要素数
	int mHitTagListSize;
	// 体力
	int mHitPoint;

	// 移動速度
	float mMoveSpeed;

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