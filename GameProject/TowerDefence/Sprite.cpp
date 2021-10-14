#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_TextureName"> �e�N�X�`���̃p�X </param>
Sprite::Sprite(const std::string _TextureName)
	:GameObject(Tag::eOther)
{
	mSpriteComponent = new SpriteComponent(this);

	mSpriteTexture = RENDERER->GetTexture(_TextureName);
	mSpriteComponent->SetTexture(mSpriteTexture);
}
