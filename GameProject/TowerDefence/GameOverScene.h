#pragma once

/// <summary>
/// ゲームオーバーシーン
/// </summary>
class GameOverScene : public SceneBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameOverScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameOverScene();

	/// <summary>
	/// シーンの更新
	/// </summary>
	/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
	/// <returns> シーンクラスのポインタ </returns>
	SceneBase* Update(const InputState& _KeyState)override;

private:
};