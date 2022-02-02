#pragma once

class PlayerObjectStateDeath : public PlayerObjectStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerObjectStateDeath();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerObjectStateDeath() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_owner"> プレイヤー(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	/// <returns> プレイヤーの状態 </returns>
	PlayerState Update(PlayerObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// プレイヤーの状態が変更して、最初に1回だけ呼び出される関数
	/// </summary>
	/// <param name="_owner"> プレイヤー(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void Enter(PlayerObject* _owner, const float _DeltaTime)override;

private:

	// 更新をやめるか
	bool mIsDead;

public:// ゲッターセッター

	/// <summary>
	/// 更新をやめるかのフラグを取得
	/// </summary>
	/// <returns> 更新をやめるかのフラグ </returns>
	bool GetIsDead() { return mIsDead; }
};