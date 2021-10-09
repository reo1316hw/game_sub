#include "Pch.h"

int UIComponent::mUIid = 0;

UIComponent::UIComponent(GameObject* _owner, int _drawOrder)
	: Component(_owner)
	, mTexture(nullptr)
	, mDrawOrder(_drawOrder)
	, mTextureWidth(0)
	, mTextureHeight(0)
	, mVisible(true)
	, mMyUIid(mUIid)
{
	mUIid++;
	//レンダラーにポインターを送る
	RENDERER->AddUI(this);
}

UIComponent::~UIComponent()
{
	mUIid--;
	//レンダラーからポインタを削除する
	RENDERER->RemoveUI(this);
}

/*
@brief	描画処理
@param _shader 使用するシェーダークラスのポインタ
*/
void UIComponent::Draw(Shader* _shader, const Vector3& _offset)
{
	//画像情報が空でないか、親オブジェクトが未更新状態でないか
	if (mTexture && mOwner->GetState() != State::Dead)
	{
		Matrix4 scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(mTextureWidth),
			static_cast<float>(mTextureHeight),
			1.0f);

		// スクリーン位置の平行移動
		Matrix4 transMat = Matrix4::CreateTranslation(
			Vector3(_offset.x - (mTextureWidth * 8.5f),
				(mTextureHeight * 5.0f) - _offset.y, 0.0f));

		Matrix4 world = scaleMatrix * transMat;

		/*Matrix4 scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(textureWidth),
			static_cast<float>(textureHeight),
			1.0f);

		Matrix4 world = scaleMatrix * owner->GetWorldTransform();*/

		_shader->SetMatrixUniform("uWorldTransform", world);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mTexture->GetTextureID());
		_shader->SetIntUniform("uSpriteTexture", 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	}
}

/*
@fn テクスチャをセットし縦横の長さを計算する
@param _texture 使用するテクスチャのポインタ
*/
void UIComponent::SetTexture(Texture* _texture)
{
	mTexture = _texture;
	mTextureWidth = mTexture->GetWidth();
	mTextureHeight = mTexture->GetHeight();
}
