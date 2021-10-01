#pragma once

class PlayerObjectStateAttack02 : public PlayerObjectStateBase
{
public:
	PlayerObjectStateAttack02();
	~PlayerObjectStateAttack02();
	PlayerState Update(PlayerObject* _owner, float _deltaTime)override;
	void Inipt(class PlayerObject* _owner, const InputState& _keyState)override;
	void        Enter(class PlayerObject* _owner, float _deltaTime)override;
	void        Exit(class PlayerObject* _owner, float _deltaTime)override;

private:
};