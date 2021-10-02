#pragma once

class PlayerObjectStateDashAttack : public PlayerObjectStateBase
{
public:

	PlayerObjectStateDashAttack();

	~PlayerObjectStateDashAttack();

	PlayerState Update(PlayerObject* _owner, float _deltaTime)override;

	void Input(class PlayerObject* _owner, const InputState& _keyState)override;

	void Enter(class PlayerObject* _owner, float _deltaTime)override;

private:

	// ƒtƒŒ[ƒ€”
	size_t mNumFrame;
};