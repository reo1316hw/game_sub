#include "SandEffectManager.h"
#include "SandEffect.h"
SandEffectManager::SandEffectManager(GameObject* _owner, SceneBase::Scene _sceneTag, const Tag& _objectTag)
	:GameObject(_sceneTag, _objectTag)
{
	owner = _owner;
	state = ParticleState::PARTICLE_DISABLE;
	prePos = Vector3::Zero;
	sceneTag = _sceneTag;
	tag = _objectTag;
}

void SandEffectManager::UpdateGameObject(float _deltaTime)
{
	if (prePos != owner->GetPosition())
	{
		state = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		state = ParticleState::PARTICLE_DISABLE;
	}
	switch (state)
	{
	case PARTICLE_DISABLE:
		break;
	case PARTICLE_ACTIVE:

		++frameCount;
		Vector3 vel = Vector3(0.0f, 0.0f, -1.0f);
		position = owner->GetPosition();
		if (frameCount % 3 == 0)
		{
			new SandEffect(position,vel, sceneTag, tag);
		}
		break;
	}

	prePos = owner->GetPosition();
}
