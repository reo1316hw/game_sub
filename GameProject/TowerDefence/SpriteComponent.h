#pragma once

// 前方宣言
class GameObject;
class Shader;
class Texture;

/*
@file SpriteComponent.h
@brief 画像データクラスを管理し、スクリーン上に描画するクラス
*/
class SpriteComponent : public Component
{
public:

	SpriteComponent(GameObject* _owner, Texture* _texture, int _drawOrder = 100);
    SpriteComponent(GameObject* _owner, Texture* _texture, HitPointGaugeController* _hitPointGaugeController, int _drawOrder = 100);
    ~SpriteComponent();

	/*
	@brief	描画処理
	@param _shader 使用するシェーダークラスのポインタ
	*/
    virtual void Draw(Shader* _shader);
protected:
	
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

public://ゲッターセッター

	/*
	@return 描画順
	*/
	int GetDrawOrder() { return mDrawOrder; }

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
};

