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
	/// <param name="_Alpha"> テクスチャの透明度 </param>
	/// <param name="_Scale"> テクスチャの拡大サイズ </param>
	Sprite(const std::string _TextureName, const bool& _ReUseGameObject = false, const float _Alpha = 1.0f, const Vector3& _Scale = Vector3(1.0f, 1.0f, 1.0f));

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Sprite() {};

	/// <summary>
	/// スプライト画像を変更する
	/// </summary>
	/// <param name="_TextureName"> テクスチャのパス </param>
	void ChangeSprite(const std::string _TextureName);

private:

	// スクリーン上に描画するクラスのポインタ
	SpriteComponent* mSpriteComponent;

public:// ゲッターセッター

	/// <summary>
	/// スクリーン上に描画するクラスのポインタ取得
	/// </summary>
	/// <returns> スクリーン上に描画するクラスのポインタ </returns>
	SpriteComponent* GetSpriteComponentPtr() { return mSpriteComponent; }
};

