#pragma once

/// <summary>
/// エネミーの追跡状態
/// </summary>
class EnemyObjectStateTrack : public EnemyObjectStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	EnemyObjectStateTrack(PlayerObject* _playerPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyObjectStateTrack() {};

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

	// ヒットするオブジェクトのリスト
	Tag mHitTagList[4];

	// 状態遷移確率
	const int MStateTransitionProbability;
	// プレイヤーの1段階目の通常攻撃のダメージ値
	const int MDamageValuePlayerFirstAttack;
	// 状態を変えるための距離
	const float MTransitionStateDistance;
	// ベクトルを短くする値
	const float MVecShortenVelue;
	// 引き離しベクトルの長さ
	const float MSeparationVecLength;

	// ダメージを受けたか
	bool mIsDamage;

	// ダメージ値
	int mDamageValue;
	// ヒットする相手のリストの要素数
	int mHitTagListSize;

	// 移動速度
	float mMoveSpeed;

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