#pragma once

/// <summary>
/// 全力疾走を始める状態
/// </summary>
class PlayerObjectStateSprintStart : public PlayerObjectStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerObjectStateSprintStart();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerObjectStateSprintStart() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_owner"> プレイヤー(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	/// <returns> プレイヤーの状態 </returns>
	PlayerState Update(PlayerObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// 入力処理
	/// </summary>
	/// <param name="_owner"> プレイヤー(親)のポインタ </param>
	/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
	void Input(PlayerObject* _owner, const InputState& _KeyState)override;

	/// <summary>
	/// プレイヤーの状態が変更して、最初に1回だけ呼び出される関数
	/// </summary>
	/// <param name="_owner"> プレイヤー(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void Enter(PlayerObject* _owner, const float _DeltaTime)override;

private:

	/// <summary>
	/// 移動処理
	/// </summary>
	/// <param name="_owner"> プレイヤー(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void MoveCalc(PlayerObject* _owner, const float _DeltaTime);

	// 移動速度
	const float MMoveSpeed;
	// 最大速度
	const float MMaxSpeed;
	// アニメーションの再生速度
	const float MPlayRate;
	// 向きのしきい値
	const float MDirThreshold;
};