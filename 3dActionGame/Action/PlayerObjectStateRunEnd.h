#pragma once
#include "PlayerObjectStateBase.h"

class PlayerObjectStateRunEnd : public PlayerObjectStateBase
{
public:
	PlayerObjectStateRunEnd();
	~PlayerObjectStateRunEnd();
	PlayerState Update(PlayerObject* _owner, float _deltaTime)override;
	void Inipt(class PlayerObject* _owner, const InputState& _keyState)override;
	void Enter(class PlayerObject* _owner, float _deltaTime)override;
	void Exit(class PlayerObject* _owner, float _deltaTime)override;
private:
	void MoveCalc(PlayerObject* _owner, float _deltaTime);

	bool mIsIdle;
	bool mIsAttack;
};