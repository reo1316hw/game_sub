#pragma once

// ‘O•ûéŒ¾
class MeshComponent;
class Mesh;
class BoxCollider;

class GroundObject : public GameObject
{
public:

	GroundObject(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName ,const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	~GroundObject();

	void UpdateGameObject(float _deltaTime)override;

private:

	const float DOWN_SPEED = 10;

	void OnCollision(const GameObject& _hitObject)override;
};