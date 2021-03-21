#include "Sprite.h"
#include "SceneBase.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "Texture.h"

Sprite::Sprite(const std::string _fileName)
	:GameObject(Tag::Other, SceneBase::Scene::other)
{
	spriteComponent = new SpriteComponent(this);

	spriteTexture = RENDERER->GetTexture(_fileName);
	spriteComponent->SetTexture(spriteTexture);
}
