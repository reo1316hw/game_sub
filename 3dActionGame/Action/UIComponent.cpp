#include "UIComponent.h"
#include "Texture.h"
#include "Shader.h"
#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"

int UIComponent::UIid = 0;

UIComponent::UIComponent(GameObject* _owner, int _drawOrder)
	:Component(_owner)
	, texture(nullptr)
	, drawOrder(_drawOrder)
	, textureWidth(0)
	, textureHeight(0)
	, visible(true)
	, myUIid(UIid)
{
	UIid++;
	//レンダラーにポインターを送る
	RENDERER->AddUI(this);
}

UIComponent::~UIComponent()
{
	UIid--;
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
	if (texture && mOwner->GetState() != State::Dead)
	{
		Matrix4 scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(textureWidth),
			static_cast<float>(textureHeight),
			1.0f);

		// スクリーン位置の平行移動
		Matrix4 transMat = Matrix4::CreateTranslation(
			Vector3(_offset.x - (textureWidth * 8.5f),
				(textureHeight * 5.0f) - _offset.y, 0.0f));

		Matrix4 world = scaleMatrix * transMat;

		/*Matrix4 scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(textureWidth),
			static_cast<float>(textureHeight),
			1.0f);

		Matrix4 world = scaleMatrix * owner->GetWorldTransform();*/

		_shader->SetMatrixUniform("uWorldTransform", world);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
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
	texture = _texture;
	textureWidth = texture->GetWidth();
	textureHeight = texture->GetHeight();
}
