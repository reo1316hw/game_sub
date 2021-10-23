#pragma once

/// <summary>
/// キューブマップの管理と描画を行う
/// </summary>
class CubeMapComponent : public Component
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> 親クラスのポインタ </param>
	CubeMapComponent(GameObject* _owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CubeMapComponent();

	/// <summary>
	/// texture生成処理
	/// </summary>
	/// <param name="_TextureName"> 使用するtextureのファイルパス </param>
	void CreateTexture(const std::string& _TextureName);

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="_shader"> 使用するシェーダークラスのポインタ </param>
	void Draw(Shader* _shader);

private:

	// 描画するかのフラグ
	bool mIsVisible;

	// 輝度情報
	float mLuminance;

	// テクスチャのポインタ
	Texture* mTexture;

public:// ゲッターセッター

	/// <summary>
	/// スカイボックスに使用しているテクスチャのポインタを取得
	/// </summary>
	/// <returns> スカイボックスに使用しているテクスチャのポインタ </returns>
	Texture* GetSkyBoxTexture() { return mTexture; }

	/// <summary>
	/// キューブを表示するかのフラグを設定
	/// </summary>
	/// <param name="_isVisible"> キューブを表示するかのフラグ </param>
	void SetIsVisible(bool _isVisible) { mIsVisible = _isVisible; }

	/// <summary>
	/// 輝度情報を設定
	/// </summary>
	/// <param name="_luminance"> 輝度情報 </param>
	void SetLuminance(float _luminance) { mLuminance = _luminance; }
};

