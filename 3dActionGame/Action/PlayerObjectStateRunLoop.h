#pragma once
#include "PlayerObjectStateBase.h"

class PlayerObjectStateRunLoop : public PlayerObjectStateBase
{
public:
	PlayerObjectStateRunLoop(bool _isDrawnSword);
	~PlayerObjectStateRunLoop();
	PlayerState Update(PlayerObject* _owner, float _deltaTime) override;
	void Inipt(class PlayerObject* _owner, const InputState& _keyState);
	void Enter(class PlayerObject* _owner, float _deltaTime)override;
private:
	void MoveCalc(PlayerObject* _owner, float _deltaTime);

	bool mIsIdle;
	bool mIsRunStart;
	bool mIsAttack;
	bool mIsDrawnSword;

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