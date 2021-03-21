#pragma once
#include "PlayerObjectStateBase.h"

class PlayerObjectStateRunEnd : public PlayerObjectStateBase
{
public:
	PlayerObjectStateRunEnd();
	~PlayerObjectStateRunEnd();
	PlayerState Update(PlayerObject* _owner, float _deltaTime)override;
	void Inipt(class PlayerObject* _owner, const InputState& _keyState)override;
	void Enter(class PlayerObject* _owner, float _deltaTime)override;
	void Exit(class PlayerObject* _owner, float _deltaTime)override;
private:
	void MoveCalc(PlayerObject* _owner, float _deltaTime);

	bool mIsIdle;
	bool mIsAttack;
	float mElapseTime;    // ���̃X�e�[�g�ɓ����Ă���̌o�ߎ���
	float mTotalAnimTime; // �A�j���[�V����������

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

	const float cStopTime = 1.0f;
};