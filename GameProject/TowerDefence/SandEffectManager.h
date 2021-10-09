#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"
class SandEffectManager :
	public GameObject
{
public:
	SandEffectManager(GameObject* _owner, SceneBase::Scene _sceneTag , const Tag& _objectTag);
	~SandEffectManager() {};

	void UpdateGameObject(float _deltaTime)override;
	
private:
	GameObject* owner;
	ParticleState state;
	Vector3 prePos;
	SceneBase::Scene sceneTag;
	Tag tag;
	int frameCount;
	int scene;
};

