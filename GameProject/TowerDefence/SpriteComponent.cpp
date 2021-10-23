#include "pch.h"

SpriteComponent::SpriteComponent(GameObject * _owner, Texture* _texture, int _drawOrder)
    : Component(_owner)
    , mDrawOrder(_drawOrder)
    , mTextureWidth(0)
    , mTextureHeight(0)
	, mVisible(true)
	, mHitPointGaugeControllerPtr(nullptr)
    , mTexture(_texture)
{
	mTextureWidth = mTexture->GetWidth();
	mTextureHeight = mTexture->GetHeight();

	//レンダラーにポインターを送る
	RENDERER->AddSprite(this);
}

SpriteComponent::SpriteComponent(GameObject* _owner, Texture* _texture, HitPointGaugeController* _hitPointGaugeController, int _drawOrder)
	: Component(_owner)
	, mDrawOrder(_drawOrder)
	, mTextureWidth(0)
	, mTextureHeight(0)
	, mVisible(true)
	, mHitPointGaugeControllerPtr(_hitPointGaugeController)
	, mTexture(_texture)
{
	mTextureWidth = mTexture->GetWidth();
	mTextureHeight = mTexture->GetHeight();

	//レンダラーにポインターを送る
	RENDERER->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	//レンダラーからポインタを削除する
	RENDERER->RemoveSprite(this);
}

/*
@brief	描画処理
@param _shader 使用するシェーダークラスのポインタ
*/
void SpriteComponent::Draw(Shader * _shader)
{
	//画像情報が空でないか、親オブジェクトが未更新状態でないか
	if (mTexture && mOwner->GetState() == State::eDead)
	{
		return;
	}

	// hpゲージを制御するコンポーネントクラスがあったらテクスチャの横幅を更新する
	if (mHitPointGaugeControllerPtr != nullptr)
	{
		mTextureWidth = mHitPointGaugeControllerPtr->GetTextureWidthAfterChange();
	}

	Matrix4 scaleMatrix = Matrix4::CreateScale(
		static_cast<float>(mTextureWidth),
		static_cast<float>(mTextureHeight),
		1.0f);

	Matrix4 world = scaleMatrix * mOwner->GetWorldTransform();

	_shader->SetMatrixUniform("uWorldTransform",world);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTexture->GetTextureID());
	_shader->SetIntUniform("uSpriteTexture", 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);	
}