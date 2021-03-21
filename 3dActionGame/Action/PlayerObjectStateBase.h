#pragma once
#include "PlayerObject.h"

class InputSystem;

class PlayerObjectStateBase
{
public:
	PlayerObjectStateBase() {};
	virtual ~PlayerObjectStateBase() {};
	virtual PlayerState Update(class PlayerObject* _owner, float _deltaTime) = 0;
	virtual void Inipt(class PlayerObject* _owner, const InputState& _keyState) = 0;
	virtual void Enter(class PlayerObject* _owner, float _deltaTime) {};
	virtual void Exit(class PlayerObject* _owner, float _deltaTime) {};
protected:
	////上方向(ジャンプ用)
	//Vector3 jumpVec;
	//// ジャンプスピード
	//const float JUMP_SPEED = 1000.0f;
private:
};