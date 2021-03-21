#pragma once
#include "GameObject.h"
#include <string>

class MeshComponent;
class Mesh;
class BoxCollider;

class GroundObject : public GameObject
{
public:
	GroundObject(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName ,const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	//GroundObject(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName);
	~GroundObject();

	void UpdateGameObject(float _deltaTime)override;
private:
	const float DOWN_SPEED = 10;

	void OnCollision(const GameObject& _hitObject)override;
};