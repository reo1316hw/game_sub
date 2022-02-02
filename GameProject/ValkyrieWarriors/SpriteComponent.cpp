#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
/// <param name="_texture"> テクスチャのポインタ </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_DrawOrder"> 描画の順番 </param>
SpriteComponent::SpriteComponent(GameObject* _owner, Texture* _texture, const int& _DrawOrder)
    : Component(_owner)
    , mDrawOrder(_DrawOrder)
	, mVisible(true)
	, mTextureWidth(0)
	, mTextureHeight(0)
    , mTexture(_texture)
{
	mTextureWidth = mTexture->GetWidth();
	mTextureHeight = mTexture->GetHeight();

	//レンダラーにポインターを送る
	RENDERER->AddSprite(this);
}

/// <summary>
/// デストラクタ
/// </summary>
SpriteComponent::~SpriteComponent()
{
	//レンダラーからポインタを削除する
	RENDERER->RemoveSprite(this);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="_shader"> 使用するシェーダークラスのポインタ </param>
void SpriteComponent::Draw(Shader * _shader)
{
	//画像情報が空でないか、親オブジェクトが未更新状態でないか
	if (mTexture && mOwner->GetState() == State::eDead)
	{
		return;
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

/// <summary>
/// テクスチャを設定し、縦横の長さを計算する
/// </summary>
/// <param name="_texture"> テクスチャクラスのポインタ </param>
void SpriteComponent::SetTexture(Texture* _texture)
{
	mTexture = _texture;
	mTextureWidth = mTexture->GetWidth();
	mTextureHeight = mTexture->GetHeight();
}
