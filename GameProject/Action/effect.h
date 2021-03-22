#pragma once
#include "effectBase.h"

class Effect : public EffectBase
{
public:
	Effect(const Vector3& _pos, const Vector3& _velocity, const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	~Effect() {};

	void UpdateGameObject(float _deltaTime)override;

private:
	GameObject* owner;
	float mScale;
	float mAlpha;
};

