#pragma once

/// <summary>
/// 2段階目の攻撃
/// </summary>
class PlayerObjectStateSecondAttack : public PlayerObjectStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerObjectStateSecondAttack();

	/// <summary>
    /// デストラクタ
    /// </summary>
	~PlayerObjectStateSecondAttack() {};

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

	// 攻撃時の速度
	const float MAttackSpeed;
	// アニメーションの再生速度
	const float MPlayRate;

	// コンボ有効フレーム
	const int MValidComboFrame;

	// フレーム数
	size_t mNumFrame;
};