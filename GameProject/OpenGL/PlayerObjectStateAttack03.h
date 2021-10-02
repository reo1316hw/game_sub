#pragma once

class PlayerObjectStateAttack03 : public PlayerObjectStateBase
{
public:

	PlayerObjectStateAttack03();

	~PlayerObjectStateAttack03();

	PlayerState Update(PlayerObject* _owner, float _deltaTime)override;

	void Enter(class PlayerObject* _owner, float _deltaTime)override;

private:
};