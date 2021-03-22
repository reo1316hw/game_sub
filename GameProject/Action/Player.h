#pragma once
#include "GameObject.h"

class SkeletalMeshComponent;
class MeshComponent;
class Mesh;

class Player:public GameObject
{
public:
	Player(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag);
	~Player();

	void UpdateGameObject(float _deltaTime)override;
	void GameObjectInput(const InputState& _keyState)override;
	//void PausingUpdateGameObject()override;

private:
	//3D���f���̕`����s���N���X
	SkeletalMeshComponent* skeltalMeshComponent;

	MeshComponent* meshComponent;
	Mesh* mesh;

	int frameCount;

	// �ړ����x
	const float PLAYER_SPEED = 20.0f;
	
	void OnCollision(const GameObject& _hitObject)override;
};

