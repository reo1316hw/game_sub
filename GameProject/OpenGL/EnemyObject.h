#pragma once

// ëOï˚êÈåæ
class SkeletalMeshComponent;
class MeshComponent;
class Mesh;
class BoxCollider;

class EnemyObject : public GameObject
{
public:
	EnemyObject(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const char* _gpskelName, const char* _gpanimName, const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	~EnemyObject();
	//PlayerObject(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const char* _gpskelName, const char* _gpanimName);

	void UpdateGameObject(float _deltaTime)override;
	void SelfRotation(Vector3 _axis, float _angle);

	//void GameObjectInput(const InputState& _keyState)override;
	//void PausingUpdateGameObject()override;

private:
	Vector3 mOffsetPos;

	// à⁄ìÆë¨ìx
	const float ENENY_SPEED = 20.0f;

	void OnCollision(const GameObject& _hitObject)override;
};

