#pragma once

/// <summary>
/// 死亡状態
/// </summary>
class EnemyObjectStateDeath : public EnemyObjectStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
    /// <param name="_playerPtr"> プレイヤーのポインタ </param>
	EnemyObjectStateDeath(PlayerObject* _playerPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyObjectStateDeath() {};

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

private:

	// アニメーションの再生速度
	const float MPlayRate;
	// 減速値
	const float MDecelerationSpeed;
	
		// 死亡時の速度
	float mDeathSpeed;

	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;

	// 座標
	Vector3 mPosition;
	// プレイヤーに向いたベクトル
	Vector3 mDirPlayerVec;
};