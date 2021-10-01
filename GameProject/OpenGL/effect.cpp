#include "effect.h"

Effect::Effect(const Vector3& _pos, const Vector3& _velocity, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: EffectBase(_pos, _velocity, 20, _objectTag, _sceneTag)
{
	mScale = 1000.0f;
	mAlpha = 1.0f;
	particle->SetScale(mScale);
	particle->SetAlpha(mAlpha);
	particle->SetColor(Vector3(1.0f, 0.0f, 0.0f));
}

void Effect::UpdateGameObject(float _deltaTime)
{	
	EffectBase::LifeCountDown();

	if (lifeCount >= 0)
	{
		position += velocity * 10.0f;

		mScale += 5.0f;
		mAlpha -= 0.05f;
		particle->SetScale(mScale);
		particle->SetAlpha(mAlpha);
		SetPosition(position);
	}

	if (lifeCount <= 0)
	{
		state = State::Dead;
	}
}
