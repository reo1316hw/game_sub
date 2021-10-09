#include "pch.h"

Sprite::Sprite(const std::string _fileName)
	:GameObject(Tag::eOther, SceneBase::Scene::other)
{
	mSpriteComponent = new SpriteComponent(this);

	mSpriteTexture = RENDERER->GetTexture(_fileName);
	mSpriteComponent->SetTexture(mSpriteTexture);
}
