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
	Sprite(const std::string _TextureName);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Sprite() {};

private:

	// テクスチャのポインタ
	Texture* mSpriteTexture;

	// スクリーン上に描画するクラスのポインタ
	SpriteComponent* mSpriteComponent;
};

