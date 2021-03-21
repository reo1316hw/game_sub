#include "EffectManager.h"
#include "PlayerObject.h"

EffectManager::EffectManager(GameObject* _owner, const Tag& _objectTag, SceneBase::Scene _sceneTag)
	:GameObject(_objectTag,_sceneTag)
{
	owner = _owner;
	sceneTag = _sceneTag;
	tag = _objectTag;
}

void EffectManager::UpdateGameObject(float _deltaTime)
{

}
