#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_TextureName"> �e�N�X�`���̃p�X </param>
/// <param name="_ReUseGameObject"> �ė��p���邩 </param>
Sprite::Sprite(const std::string _TextureName, const bool& _ReUseGameObject)
	:GameObject(Tag::eOther, _ReUseGameObject)
{
	Texture* texture = RENDERER->GetTexture(_TextureName);
	mSpriteComponent = new SpriteComponent(this, texture);
}