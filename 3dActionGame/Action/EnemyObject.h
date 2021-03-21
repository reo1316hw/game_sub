#pragma once
#include "GameObject.h"
#include  <string>

class SkeletalMeshComponent;
class MeshComponent;
class Mesh;
class BoxCollider;

class EnemyObject :public GameObject
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
	//3Dモデルの描画を行うクラス
	SkeletalMeshComponent* skeltalMeshComponent;
	MeshComponent* meshComponent;
	Mesh* mesh;

	BoxCollider* boxCollider;

	Vector3 offsetPos;

	// 移動速度
	const float ENENY_SPEED = 20.0f;

	void OnCollision(const GameObject& _hitObject)override;
};

