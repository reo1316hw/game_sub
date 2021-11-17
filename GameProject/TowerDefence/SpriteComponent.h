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
	/// <param name="_Scale"> テクスチャの拡大サイズ </param>
	/// <param name="_DrawOrder"> 描画の順番 </param>
	SpriteComponent(GameObject* _owner, Texture* _texture, const Vector2& _Scale , const int& _DrawOrder = 100);

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
	/// <param name="_texture"> テクスチャのポインタ </param>
	/// <param name="_hitPointGaugeController"> hpゲージを制御するクラスのポインタ </param>
	/// <param name="_Scale"> テクスチャの拡大サイズ </param>
	/// <param name="_DrawOrder"> 描画の順番 </param>
    SpriteComponent(GameObject* _owner, Texture* _texture, HitPointGaugeController* _hitPointGaugeController,
		const Vector2& _Scale, const int& _DrawOrder = 100);

	/// <summary>
	/// デストラクタ
	/// </summary>
    ~SpriteComponent();

    /// <summary>
    /// 描画処理
    /// </summary>
    /// <param name="_shader"> 使用するシェーダークラスのポインタ </param>
    virtual void Draw(Shader* _shader);

private:
	
	// テクスチャの大きさ
	const Vector2 MScale;

	// 描画を行うか
	bool mVisible;

	// 描画される順番（数値が少ないほど早く更新される）
    int mDrawOrder;
	// テクスチャの横幅
    int mTextureWidth;
	// テクスチャの縦幅
    int mTextureHeight;

	// hpゲージを制御するコンポーネントクラスのポインタ
	HitPointGaugeController* mHitPointGaugeControllerPtr;
	// クラスのポインタ
	Texture* mTexture;

public:// ゲッターセッター

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

