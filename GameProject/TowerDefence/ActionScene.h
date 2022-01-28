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

	// ゲームクリアシーンに遷移するタイミング
	const int MTimingTransitionGameClear;
	// ゲームオーバーシーンに遷移するタイミング
	const int MTimingTransitionGameOver;
	// 画角
	const float MAngleOfView;
	// 光源までの距離
	const float MLightDistance;

	// ゲームクリアシーンに遷移するまでのカウント
	int mGameClearTransitionUntilCount;
	// ゲームオーバーシーンに遷移するまでのカウント
	int mGameOverTransitionUntilCount;

	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
	// ボスのポインタ
	BossObject* mBossPtr;
	// カメラのポインタ
	MainCameraObject* mMainCameraPtr;
};

