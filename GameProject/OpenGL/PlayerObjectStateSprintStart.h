#pragma once

class PlayerObjectStateSprintStart : public PlayerObjectStateBase
{
public:

	PlayerObjectStateSprintStart();

	~PlayerObjectStateSprintStart();

	PlayerState Update(PlayerObject* _owner, float _deltaTime)override;

	void Input(class PlayerObject* _owner, const InputState& _keyState)override;

	void Enter(class PlayerObject* _owner, float _deltaTime)override;

private:

	void MoveCalc(PlayerObject* _owner, float _deltaTime);
};