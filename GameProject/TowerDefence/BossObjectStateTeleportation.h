#pragma once

/// <summary>
/// ボスの瞬間移動
/// </summary>
class BossObjectStateTeleportation : public BossObjectStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	BossObjectStateTeleportation(PlayerObject* _playerPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BossObjectStateTeleportation() {};

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

private:

	// テレポート終わるタイミング
	const int MTimingTeleportationEnding;
	// 状態を変えるための距離
	const float MTransitionStateDistance;

	// ダメージを受けたか
	bool mIsDamage;

	// テレポート終わりまでのカウント
	int mUntilTeleportationEndingCount;

	// 座標
	Vector3 mPosition;
	// テレポートする向き
	Vector3 mTeleportationVec;

	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
};