#pragma once
#include "PlayerObjectStateBase.h"

class PlayerObjectStateAttack03 : public PlayerObjectStateBase
{
public:
	PlayerObjectStateAttack03();
	~PlayerObjectStateAttack03();
	PlayerState Update(PlayerObject* _owner, float _deltaTime)override;
	void Inipt(class PlayerObject* _owner, const InputState& _keyState)override;
	void        Enter(class PlayerObject* _owner, float _deltaTime)override;
	void        Exit(class PlayerObject* _owner, float _deltaTime)override;
private:
	float mElapseTime;    // ���̃X�e�[�g�ɓ����Ă���̌o�ߎ���
	float mTotalAnimTime; // �A�j���[�V����������

	const float cStopTime = 1.0f;
};