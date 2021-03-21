#pragma once
#include "PlayerObjectStateBase.h"

class PlayerObjectStateSwordIdle : public PlayerObjectStateBase
{
public:
	PlayerObjectStateSwordIdle();
	~PlayerObjectStateSwordIdle();
	PlayerState Update(PlayerObject* _owner, float _deltaTime) override;
	void Inipt(class PlayerObject* _owner, const InputState& _keyState);
	void Enter(class PlayerObject* _owner, float _deltaTime)override;
private:
	//�v���C���[�̏�ԑJ�ڂɎg���t���O
	bool mIsSprint;		//����o����
	bool mIsRun;		//���邩
	bool mIsAttack;		//�U�����邩
	bool swordDelivery; //�[���������ǂ���
};