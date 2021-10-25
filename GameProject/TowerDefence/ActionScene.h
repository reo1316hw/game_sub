#pragma once

/// <summary>
/// アクションシーン
/// </summary>
class ActionScene : public SceneBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ActionScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ActionScene();

	/// <summary>
	/// シーンの更新
	/// </summary>
	/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
	/// <returns> シーンクラスのポインタ </returns>
	SceneBase* Update(const InputState& _KeyState)override;

private:

	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
	// ボスのポインタ
	BossObject* mBossPtr;
};

