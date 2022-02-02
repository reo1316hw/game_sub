#pragma once
#include "GameObject.h"

class MeshComponent;

class playerblock:public GameObject
{
public:
	playerblock(const Vector3& _pos, const Vector3& _size, const Tag& objectTag);
	~playerblock();

	void UpdateGameObject(float _deltaTime)override;
	void GameObjectInput(const InputState& _keyState)override;
private:
	MeshComponent* meshComponent;

};

