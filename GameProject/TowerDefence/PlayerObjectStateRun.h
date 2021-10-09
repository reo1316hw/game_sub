#pragma once
#include "PlayerObjectStateBase.h"

class PlayerObjectStateRun : public PlayerObjectStateBase
{
public:
	PlayerObjectStateRun();
	~PlayerObjectStateRun();
	PlayerState Update(PlayerObject* _owner, float _deltaTime) override;
	void Inipt(class PlayerObject* _owner, const InputState& _keyState);
	void Enter(class PlayerObject* _owner, float _deltaTime)override;
private:
	void MoveCalc(PlayerObject* _owner, float _deltaTime);

	bool mIsIdle;
	bool mIsAttack;

	//  �L�����̌��݂̃X�s�[�h
	float charaSpeed;

	//����
	Vector3 dirVec;
	//�O�i����
	Vector3 forwardVec;
	//�E����
	Vector3 rightVec;
	// �L�����̑O�i�x�N�g��
	Vector3 charaForwardVec;
};