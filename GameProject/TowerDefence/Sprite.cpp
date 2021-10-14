#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_TextureName"> テクスチャのパス </param>
Sprite::Sprite(const std::string _TextureName)
	:GameObject(Tag::eOther)
{
	mSpriteComponent = new SpriteComponent(this);

	mSpriteTexture = RENDERER->GetTexture(_TextureName);
	mSpriteComponent->SetTexture(mSpriteTexture);
}
