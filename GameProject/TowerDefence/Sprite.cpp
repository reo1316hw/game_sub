#include "pch.h"

Sprite::Sprite(const std::string _fileName)
	:GameObject(Tag::Other, SceneBase::Scene::other)
{
	mSpriteComponent = new SpriteComponent(this);

	mSpriteTexture = RENDERER->GetTexture(_fileName);
	mSpriteComponent->SetTexture(mSpriteTexture);
}
