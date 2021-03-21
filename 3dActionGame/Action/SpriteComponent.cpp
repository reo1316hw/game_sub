#include "SpriteComponent.h"
#include "Texture.h"
#include "Shader.h"
#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"

SpriteComponent::SpriteComponent(GameObject * _owner, int _drawOrder)
    :Component(_owner)
    ,texture(nullptr)
    ,drawOrder(_drawOrder)
    ,textureWidth(0)
    ,textureHeight(0)
	, visible(true)
{
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
	if (texture&& mOwner->GetState()!=State::Dead)
	{
		Matrix4 scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(textureWidth),
			static_cast<float>(textureHeight),
			1.0f);

		Matrix4 world = scaleMatrix * mOwner->GetWorldTransform();

		_shader->SetMatrixUniform("uWorldTransform",world);
		
	/*	_shader->SetFloatUniform("uLuminance", texture->GetLuminace());*/

		//texture->SetActive();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
		_shader->SetIntUniform("uSpriteTexture", 0);

	/*	glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, emissiveTexture->GetTextureID());
		_shader->SetIntUniform("uEmissiveMap", 3);*/

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);	
	}
}

/*
@fn テクスチャをセットし縦横の長さを計算する
@param _texture 使用するテクスチャのポインタ
*/
//void SpriteComponent::SetTexture(Texture * _texture, Texture* _emissiveTexture)
//{
//	texture = _texture;
//	textureWidth = texture->GetWidth();
//	textureHeight = texture->GetHeight();
//
//	emissiveTexture = _emissiveTexture;
//	emissiveTextureWidth = emissiveTexture->GetWidth();
//	emissiveTextureHeight = emissiveTexture->GetHeight();
//}

void SpriteComponent::SetTexture(Texture* _texture)
{
	texture = _texture;
	textureWidth = texture->GetWidth();
	textureHeight = texture->GetHeight();
}
