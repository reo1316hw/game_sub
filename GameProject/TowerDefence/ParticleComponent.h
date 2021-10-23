#pragma once

/*
 @file ParticleComponent.h
 @brief 画像を管理しそれを3D空間上に描画するクラス。
*/
class ParticleComponent : public Component
{
public:

	//パーティクルに対するブレンドの種類
	typedef enum PARTICLE_BLEND_ENUM
	{
		PARTICLE_BLEND_ENUM_ALPHA,
		PARTICLE_BLEND_ENUM_ADD,
		PARTICLE_BLEND_ENUM_MULT
	}PARTICLE_ENUM;

	/*
	 @param _offset 親オブジェクトクラスと画像を描画する位置の差
	 @param _scale 画像の描画サイズ
	*/
	ParticleComponent(GameObject* _owner, Texture* _texture, float _scale = 1.0f, int _updateOrder = 100);
	ParticleComponent(GameObject* _owner, Texture* _texture, HitPointGaugeController* _hitPointGaugeControllerconst, float _scale = 1.0f, int _updateOrder = 100);
	~ParticleComponent();

	virtual void Update(float _deltaTime) override {};

	/*
	@brief　描画処理
	@param	_shader 使用するシェーダークラスのポインタ
	*/
	void Draw(class Shader* _shader);

	Matrix4 GetBillboardMatrix();

	//// カメラ距離でのソート用
	//bool operator < (const ParticleComponent& _rhs) const;
	//bool operator > (const ParticleComponent& _rhs) const;

private:

	//反転を行うか
	bool mReverce;
	//描画を行うか
	bool mVisible;

	//描画順(数字が少ないものから描画される)
	int mDrawOrder;
	//テクスチャの横幅
	int mTextureWidth;
	//テクスチャの縦幅
	int mTextureHeight;

	//サイズ
	float mScale;
	//透明度
	float mAlpha;

	//画像に乗算する色
	Vector3 mColor;
	//ブレンドタイプ
	PARTICLE_ENUM mBlendType;

	// ビルボード行列
	static Matrix4 mStaticBillboardMat;
	// カメラのワールド座標
	static Vector3 mStaticCameraWorldPos;

	// hpゲージを制御するコンポーネントクラスのポインタ
	HitPointGaugeController* mHitPointGaugeControllerPtr;

	//クラスのポインタ
	Texture* mTexture;

public: //ゲッターセッター

	/*
	@return テクスチャ
	*/
	Texture* GetTexture() { return mTexture; }

	/*
	@return ブレンドタイプ
	*/
	PARTICLE_ENUM GetBlendType() { return mBlendType; }

	/*
	@param _brendType カメラのワールド座標
	*/
	void SetBlendMode(PARTICLE_ENUM _blendType) { mBlendType = _blendType; }

	/*
	@param _mat ビルボード行列
	*/
	void SetBillboardMat(const Matrix4& _mat) {	mStaticBillboardMat = _mat; }
	
	/*
	@brief　描画をするかどうかを取得する
	@return	true : 描画する , false : 描画しない
	*/
	bool GetVisible() const { return mVisible; }

	/*
	@brief　描画をするかどうかを設定
	@param	true : 描画する , false : 描画しない
	*/
	void SetVisible(bool _visible) { mVisible = _visible; }

	/*
	@return 描画順
	*/
	int GetDrawOrder() { return mDrawOrder; }

	/*
	@param _drawOrder 描画順
	*/
	void SetDrawOrder(int _drawOrder) { mDrawOrder = _drawOrder; }

	/*
	@param _flag 反転を行うか
	*/
	void SetReverce(bool _flag) { mReverce = _flag; }
};