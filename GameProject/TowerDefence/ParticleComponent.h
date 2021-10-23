#pragma once

/// <summary>
/// 画像を管理しそれを3D空間上に描画するクラス
/// </summary>
class ParticleComponent : public Component
{
public:

	/// <summary>
	/// パーティクルに対するブレンドの種類
	/// </summary>
	typedef enum ParticleBlendType
	{
		eParticleBlendAlpha,
		eParticleBlendAdd,
		eParticleBlendMult
	}ParticleType;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
	/// <param name="_texture"> テクスチャのポインタ </param>
	/// <param name="_Scale"> 画像の描画サイズ </param>
	/// <param name="_UpdateOrder"> コンポーネントの更新順番（数値が小さいほど早く更新される）</param>
	ParticleComponent(GameObject* _owner, Texture* _texture, const Vector3& _Scale = Vector3(1.0f, 1.0f, 1.0f), const int& _UpdateOrder = 100);

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
	/// <param name="_texture"> テクスチャのポインタ </param>
	/// <param name="_hitPointGaugeControllerconst"> hpゲージを制御するクラスのポインタ </param>
	/// <param name="_Scale"> 画像の描画サイズ </param>
	/// <param name="_UpdateOrder"> コンポーネントの更新順番（数値が小さいほど早く更新される）</param>
	ParticleComponent(GameObject* _owner, Texture* _texture, HitPointGaugeController* _hitPointGaugeControllerconst, const Vector3& _Scale = Vector3(1.0f,1.0f,1.0f), const int& _updateOrder = 100);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParticleComponent();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="_shader"> 使用するシェーダークラスのポインタ </param>
	void Draw(class Shader* _shader);

	/// <summary>
	/// ビルボード行列作成
	/// </summary>
	/// <returns></returns>
	Matrix4 CreateBillboardMatrix();

private:

	// 描画を行うか
	bool mVisible;

	// 描画順(数字が少ないものから描画される)
	int mDrawOrder;
	// テクスチャの横幅
	int mTextureWidth;
	// テクスチャの縦幅
	int mTextureHeight;

	// 透明度
	float mAlpha;

	// サイズ
	Vector3 mScale;
	// 画像に乗算する色
	Vector3 mColor;
	// ビルボード行列
	Matrix4 mBillboardMat;
	// ブレンドタイプ
	ParticleType mBlendType;

	// hpゲージを制御するコンポーネントクラスのポインタ
	HitPointGaugeController* mHitPointGaugeControllerPtr;
	// クラスのポインタ
	Texture* mTexture;

public:// ゲッターセッター

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

	/// <summary>
	/// 描画順を取得
	/// </summary>
	/// <returns> 描画順 </returns>
	int GetDrawOrder() { return mDrawOrder; }

	/// <summary>
	/// 描画順を設定
	/// </summary>
	/// <param name="_drawOrder"> 描画順 </param>
	void SetDrawOrder(int _drawOrder) { mDrawOrder = _drawOrder; }

	/// <summary>
	/// ブレンドタイプを取得
	/// </summary>
	/// <returns> ブレンドタイプ </returns>
	ParticleType GetBlendType() { return mBlendType; }

	/// <summary>
	/// ブレンドタイプを設定
	/// </summary>
	/// <param name="_blendType"> ブレンドタイプ </param>
	void SetBlendMode(ParticleType _blendType) { mBlendType = _blendType; }

	/// <summary>
	/// テクスチャのポインタ取得
	/// </summary>
	/// <returns> テクスチャのポインタ </returns>
	Texture* GetTexture() { return mTexture; }
};