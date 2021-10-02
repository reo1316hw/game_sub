#pragma once

class PlayerObjectStateRunLoop : public PlayerObjectStateBase
{
public:

	PlayerObjectStateRunLoop();

	~PlayerObjectStateRunLoop();

	PlayerState Update(PlayerObject* _owner, float _deltaTime) override;

	void Input(class PlayerObject* _owner, const InputState& _keyState);

	void Enter(class PlayerObject* _owner, float _deltaTime)override;

private:

	void MoveCalc(PlayerObject* _owner, float _deltaTime);
};