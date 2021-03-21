#pragma once
#include "GameObject.h"
#include <string>

class MeshComponent;
class Mesh;
class BoxCollider;

class WallObject : public GameObject
{
public:
	WallObject(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	//WallObject(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName);
	~WallObject();

	void UpdateGameObject(float _deltaTime)override;
private:
	MeshComponent* meshComponent;
	BoxCollider* boxCollider;
	Mesh* mesh;
};