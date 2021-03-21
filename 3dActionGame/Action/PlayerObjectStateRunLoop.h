#pragma once
#include "PlayerObjectStateBase.h"

class PlayerObjectStateRunLoop : public PlayerObjectStateBase
{
public:
	PlayerObjectStateRunLoop(bool _isDrawnSword);
	~PlayerObjectStateRunLoop();
	PlayerState Update(PlayerObject* _owner, float _deltaTime) override;
	void Inipt(class PlayerObject* _owner, const InputState& _keyState);
	void Enter(class PlayerObject* _owner, float _deltaTime)override;
private:
	void MoveCalc(PlayerObject* _owner, float _deltaTime);

	bool mIsIdle;
	bool mIsRunStart;
	bool mIsAttack;
	bool mIsDrawnSword;
};