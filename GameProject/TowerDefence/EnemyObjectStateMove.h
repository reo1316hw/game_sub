#pragma once

/// <summary>
/// 移動状態
/// </summary>
class EnemyObjectStateMove : public EnemyObjectStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	EnemyObjectStateMove(PlayerObject* _playerPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyObjectStateMove() {};

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
	/// ヒットした時の処理
	/// </summary>
	/// <param name="_owner"> エネミー(親)のポインタ </param>
	/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
	void OnColision(EnemyObject* _owner, const GameObject& _HitObject)override;

private:

	/// <summary>
	/// 移動処理
	/// </summary>
	/// <param name="_owner"> エネミー(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void MoveCalc(EnemyObject* _owner, const float _DeltaTime);

	// 遷移するタイミング
	const int MTransitionTimingNum;
	// 状態を変えるための距離
	const float MTransitionStateDistance;

	// 移動しているか
	bool mIsMoving;
	// ダメージを受けたか
	bool mIsDamage;
	// エネミーと当たったか
	bool mIsHitEnemy;

	// 移動する時間のカウント変数
	int mPeriodMoveCount;

	// 移動速度
	float mMoveSpeed;

	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
};