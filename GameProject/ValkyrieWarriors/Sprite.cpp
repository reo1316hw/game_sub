#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_TextureName"> テクスチャのパス </param>
/// <param name="_ReUseGameObject"> 再利用するか </param>
/// <param name="_Alpha"> テクスチャの透明度 </param>
/// <param name="_Scale"> テクスチャの拡大サイズ </param>
Sprite::Sprite(const std::string _TextureName, const bool& _ReUseGameObject, const float _Alpha, const Vector3& _Scale)
	:GameObject(Tag::eOther, _ReUseGameObject)
{
	Texture* texture = RENDERER->GetTexture(_TextureName);

	mPosition.x -= texture->GetWidth() * 0.5f;
	SetPosition(mPosition);
	SetScale(_Scale);

	mSpriteComponent = new SpriteComponent(this, texture, _Alpha);
}

/// <summary>
/// スプライト画像を変更する
/// </summary>
/// <param name="_TextureName"> テクスチャのパス </param>
void Sprite::ChangeSprite(const std::string _TextureName)
{
	Texture* texture = RENDERER->GetTexture(_TextureName);
	mSpriteComponent->SetTexture(texture);
}
