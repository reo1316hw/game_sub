#pragma once

class PlayerObjectStateSwordIdle : public PlayerObjectStateBase
{
public:
	PlayerObjectStateSwordIdle();
	~PlayerObjectStateSwordIdle();
	PlayerState Update(PlayerObject* _owner, float _deltaTime) override;
	void Inipt(class PlayerObject* _owner, const InputState& _keyState);
	void Enter(class PlayerObject* _owner, float _deltaTime)override;
private:
};