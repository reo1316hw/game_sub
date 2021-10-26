#pragma once

// 前方宣言
class Texture;
class SpriteComponent;

/// <summary>
/// スプライト
/// </summary>
class Sprite : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_TextureName"> テクスチャのパス </param>
    /// <param name="_ReUseGameObject"> 再利用するか </param>
	Sprite(const std::string _TextureName, const bool& _ReUseGameObject = false);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Sprite() {};

private:

	// スクリーン上に描画するクラスのポインタ
	SpriteComponent* mSpriteComponent;
};

