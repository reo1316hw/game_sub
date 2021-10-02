#pragma once

class PlayerObjectStateIdle : public PlayerObjectStateBase
{
public:

	PlayerObjectStateIdle();

	~PlayerObjectStateIdle();

	PlayerState Update(PlayerObject* _owner, float _deltaTime) override;

	void Input(class PlayerObject* _owner, const InputState& _keyState);

	void Enter(class PlayerObject* _owner, float _deltaTime)override;

private:
};