#pragma once

/// <summary>
/// フェードイン用スプライトの種類
/// </summary>
enum FadeInSpriteType
{
	eWhite,
    eBlack
};

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

	// 透明度を足していくための値
	const float MPlusAlpha;
	// 画角
	const float MAngleOfView;
	// 光源までの距離
	const float MLightDistance;
	// スプライトの拡大サイズ
	const Vector3 MSpriteScale;

	// スプライトコンポーネントのリスト
	std::vector<SpriteComponent*> mSpriteComponentList;

	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
	// ボスのポインタ
	BossObject* mBossPtr;
	// カメラのポインタ
	MainCameraObject* mMainCameraPtr;
};

