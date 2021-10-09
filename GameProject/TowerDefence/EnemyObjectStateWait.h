#pragma once

/// <summary>
/// 待機状態
/// </summary>
class EnemyObjectStateWait : public EnemyObjectStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	EnemyObjectStateWait(PlayerObject* _playerPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyObjectStateWait() {};

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
	/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
	void OnColision(const GameObject& _HitObject)override;

private:

	// 遷移するタイミング
	const int MTransitionTimingNum;

	// 状態を変えるための距離
	const float MTransitionStateDistance;

	// ダメージを受けたか
	bool mIsDamage;

	// 遷移するためのカウント変数
	int mTransitionCount;

	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
};