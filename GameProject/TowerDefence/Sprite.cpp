#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_TextureName"> �e�N�X�`���̃p�X </param>
/// <param name="_Scale"> �e�N�X�`���̊g��T�C�Y </param>
/// <param name="_ReUseGameObject"> �ė��p���邩 </param>
Sprite::Sprite(const std::string _TextureName, const bool& _ReUseGameObject, const Vector3& _Scale)
	:GameObject(Tag::eOther, _ReUseGameObject)
{
	Texture* texture = RENDERER->GetTexture(_TextureName);

	mPosition.x -= texture->GetWidth() * 0.5f;
	SetPosition(mPosition);
	SetScale(_Scale);

	mSpriteComponent = new SpriteComponent(this, texture);
}

/// <summary>
/// �X�v���C�g�摜��ύX����
/// </summary>
/// <param name="_TextureName"> �e�N�X�`���̃p�X </param>
void Sprite::ChangeSprite(const std::string _TextureName)
{
	Texture* texture = RENDERER->GetTexture(_TextureName);
	mSpriteComponent->SetTexture(texture);
}
