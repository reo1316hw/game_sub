#pragma once

// 前方宣言
class GameObject;
class Shader;
class Texture;

/// <summary>
/// 画像データクラスを管理し、スクリーン上に描画するクラス
/// </summary>
class SpriteComponent : public Component
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
	/// <param name="_texture"> テクスチャのポインタ </param>
	/// <param name="_Alpha"> 透明度 </param>
	/// <param name="_DrawOrder"> 描画の順番 </param>
	SpriteComponent(GameObject* _owner, Texture* _texture, const float _Alpha = 1.0f, const int& _DrawOrder = 100);

	/// <summary>
	/// デストラクタ
	/// </summary>
    ~SpriteComponent();

    /// <summary>
    /// 描画処理
    /// </summary>
    /// <param name="_shader"> 使用するシェーダークラスのポインタ </param>
    virtual void Draw(Shader* _shader);
	
	/// <summary>
	/// 透明度を上げる
	/// </summary>
	/// <param name="_PlusAlpha"> 透明度を足していくための値 </param>
	/// <returns> 透明度 </returns>
	float IncreaseAlpha(const float _PlusAlpha);

	/// <summary>
	/// 透明度をリセット
	/// </summary>
	void ResetAlpha();

private:

	// 初期透明度
	const float MInitAlpha;

	// 描画を行うか
	bool mVisible;

	// 描画される順番（数値が少ないほど早く更新される）
    int mDrawOrder;
	// テクスチャの横幅
	int mTextureWidth;
	// テクスチャの縦幅
	int mTextureHeight;
	
	// 透明度
	float mAlpha;

	// テクスチャクラスのポインタ
	Texture* mTexture;

public:// ゲッターセッター

	/// <summary>
	/// テクスチャを設定し、縦横の長さを計算する
	/// </summary>
	/// <param name="_texture"> テクスチャクラスのポインタ </param>
	void SetTexture(Texture* _texture);

	/// <summary>
	/// 描画順を取得
	/// </summary>
	/// <returns> 描画順 </returns>
	int GetDrawOrder() { return mDrawOrder; }

	/// <summary>
	/// 描画をするかどうかのフラグを取得する
	/// </summary>
	/// <returns> true : 描画する , false : 描画しない </returns>
	bool GetVisible() const { return mVisible; }

	/// <summary>
	/// 描画をするかどうかのフラグを設定
	/// </summary>
	/// <param name="_visible"> 描画をするかどうかのフラグ </param>
	void SetVisible(bool _visible) { mVisible = _visible; }
};

