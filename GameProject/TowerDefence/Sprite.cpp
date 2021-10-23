#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_TextureName"> テクスチャのパス </param>
Sprite::Sprite(const std::string _TextureName)
	:GameObject(Tag::eOther)
{
	Texture* texture = RENDERER->GetTexture(_TextureName);
	mSpriteComponent = new SpriteComponent(this, texture);
}