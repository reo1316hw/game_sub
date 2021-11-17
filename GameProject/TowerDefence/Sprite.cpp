#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_TextureName"> テクスチャのパス </param>
/// <param name="_Scale"> テクスチャの拡大サイズ </param>
/// <param name="_ReUseGameObject"> 再利用するか </param>
Sprite::Sprite(const std::string _TextureName, const bool& _ReUseGameObject, const Vector2& _Scale)
	:GameObject(Tag::eOther, _ReUseGameObject)
{
	Texture* texture = RENDERER->GetTexture(_TextureName);
	mSpriteComponent = new SpriteComponent(this, texture, _Scale);
}