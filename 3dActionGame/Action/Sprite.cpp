#include "Sprite.h"
#include "SceneBase.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "Texture.h"

Sprite::Sprite(const std::string _fileName)
	:GameObject(Tag::Other, SceneBase::Scene::other)
{
	mSpriteComponent = new SpriteComponent(this);

	mSpriteTexture = RENDERER->GetTexture(_fileName);
	mSpriteComponent->SetTexture(mSpriteTexture);
}
