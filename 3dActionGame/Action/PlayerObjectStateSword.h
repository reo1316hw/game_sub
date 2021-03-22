#pragma once
#include "PlayerObjectStateBase.h"

class PlayerObjectStateSword : public PlayerObjectStateBase
{
public:
	PlayerObjectStateSword(bool _moveFlag, bool _drawnSwordFlag);
	~PlayerObjectStateSword();
	PlayerState Update(PlayerObject* _owner, float _deltaTime) override;
	void Inipt(class PlayerObject* _owner, const InputState& _keyState) override;
	void Enter(class PlayerObject* _owner, float _deltaTime) override;
private:
	void MoveCalc(PlayerObject* _owner, float _deltaTime);

	//“®‚­‚©‚Ç‚¤‚©
	bool mMoveFlag;
};