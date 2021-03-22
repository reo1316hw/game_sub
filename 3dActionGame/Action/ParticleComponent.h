#pragma once
#include "Component.h"
#include "Math.h"

/*
 @file ParticleComponent.h
 @brief 画像を管理しそれを3D空間上に描画するクラス。
*/
class ParticleComponent :
	public Component
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
	ParticleComponent(GameObject* _owner, const Vector3& _offset = Vector3(1, 1, 1), float _scale = 1.0f, int _updateOrder = 100);
	~ParticleComponent();

	virtual void Update(float _deltaTime) override {};

	/*
	@brief　描画処理
	@param	_shader 使用するシェーダークラスのポインタ
	*/
	void Draw(class Shader* _shader);

	// カメラ距離でのソート用
	bool operator < (const ParticleComponent& _rhs) const;
	bool operator > (const ParticleComponent& _rhs) const;
private:
	//親オブジェクトクラスと画像を描画する位置の差
	Vector3 mOffset;
	//画像に乗算する色
	Vector3 mColor;
	//サイズ
	float mScale;
	//透明度
	float mAlpha; 
	//テクスチャID
	int mTextureID; 
	//ブレンドタイプ
	PARTICLE_ENUM mBlendType;
	//描画を行うか
	bool mVisible;
	// ビルボード行列
	static Matrix4 mStaticBillboardMat; 
	// カメラのワールド座標
	static Vector3 mStaticCameraWorldPos;
	//描画順(数字が少ないものから描画される)
	int mDrawOrder;
	//反転を行うか
	bool mReverce;
public: //ゲッターセッター
	/*
	@return テクスチャID
	*/
	int GetTextureID() { return mTextureID; }
	/*
	@param _texId テクスチャID
	*/
	void SetTextureID(int _texId) { mTextureID = _texId; }
	/*
	@return ブレンドタイプ
	*/
	PARTICLE_ENUM GetBlendType() { return mBlendType; }
	/*
	@param _color 画像に乗算する色
	*/
	void SetColor(const Vector3& _color) { mColor = _color; }
	/*
	@param _alfa 透明度0~1
	*/
	void SetAlpha(float _alpha) { mAlpha = _alpha; }
	/*
	@param サイズ
	*/
	void SetScale(float _scale) { mScale = _scale; }
	/*
	@param _mat ビルボード行列
	*/
	void SetBillboardMat(const Matrix4& _mat) {	mStaticBillboardMat = _mat;	}
	/*
	@param _brendType カメラのワールド座標
	*/
	void SetBlendMode(PARTICLE_ENUM _blendType){mBlendType = _blendType;	}
	/*
	@brief　描画をするかどうかを設定
	@param	true : 描画する , false : 描画しない
	*/
	void SetVisible(bool _visible) { mVisible = _visible; }

	/*
	@brief　描画をするかどうかを取得する
	@return	true : 描画する , false : 描画しない
	*/
	bool GetVisible() const { return mVisible; }

	/*
	@param _drawOrder 描画順
	*/
	void SetDrawOrder(int _drawOrder) { mDrawOrder = _drawOrder; }

	/*
	@return 描画順
	*/
	int GetDrawOrder() { return mDrawOrder; }

	/*
	@param _offset 親オブジェクトの座標と描画位置の差
	*/
	void SetOffSet(Vector3 _offset) { mOffset = _offset; };

	/*
	@param _flag 反転を行うか
	*/
	void SetReverce(bool _flag) { mReverce = _flag; }
};

Matrix4 GetBillboardMatrix();
