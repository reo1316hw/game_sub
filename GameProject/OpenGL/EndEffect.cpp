#include "EndEffect.h"
#include "Renderer.h"
#include "ParticleComponent.h"
#include "SceneBase.h"
#include "GameObject.h"

EndEffect::EndEffect(Vector3 _pos, Vector3 _vel, SceneBase::Scene _sceneTag, const Tag& _objectTag)
	:ParticleEffectBase(_pos, _vel, 30, "Assets/Glass.png", _sceneTag, _objectTag)
{
	mAlpha = 1.0f;
	mScale = 32.0f;
	particle->SetAlpha(mAlpha);
	particle->SetScale(mScale);
	particle->SetColor(Vector3(0.0f,0.72f,0.79f));
	particle->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM_ALPHA);
	velocity = _vel;
	speed = 1.5f;
}

void EndEffect::UpdateGameObject(float _deltaTime)
{
	ParticleEffectBase::LifeCountDown();

	if (lifeCount > 0)
	{
		mAlpha -= 0.001f;
		mScale += 2.0f;
		particle->SetAlpha(mAlpha);
		particle->SetScale(mScale);
		if (lifeCount <= 15)
		{
			velocity = velocity * speed;
			velocity.y *= -1.0f;
		}
		else
		{
			velocity = velocity * speed;
		}
		position = position + velocity;
		SetPosition(position);
	}

	if (lifeCount <= 0)
	{
		particle->SetVisible(false);
	}
}
