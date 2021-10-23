#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_TextureName"> �e�N�X�`���̃p�X </param>
Sprite::Sprite(const std::string _TextureName)
	:GameObject(Tag::eOther)
{
	Texture* texture = RENDERER->GetTexture(_TextureName);
	mSpriteComponent = new SpriteComponent(this, texture);
}