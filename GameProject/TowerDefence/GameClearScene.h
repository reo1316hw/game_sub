#pragma once

/// <summary>
/// ゲームクリアシーン
/// </summary>
class GameClearScene : public SceneBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameClearScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameClearScene();

	/// <summary>
	/// シーンの更新
	/// </summary>
	/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
	/// <returns> シーンクラスのポインタ </returns>
	SceneBase* Update(const InputState& _KeyState)override;

private:

	// スプライトの拡大サイズ
	const Vector2 MSpriteScale;
};

