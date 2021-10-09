#pragma once
#include "PlayerObjectStateBase.h"

class PlayerObjectStateDrawnSword : public PlayerObjectStateBase
{
public:
	PlayerObjectStateDrawnSword(bool _moveFlag);
	~PlayerObjectStateDrawnSword();
	PlayerState Update(PlayerObject* _owner, float _deltaTime) override;
	void Inipt(class PlayerObject* _owner, const InputState& _keyState) override;
	void Enter(class PlayerObject* _owner, float _deltaTime) override;
private:
	void MoveCalc(PlayerObject* _owner, float _deltaTime);

	bool mIsIdle;
	bool mIsRunStart;
	bool mIsAttack;
	//�������ǂ���
	bool moveFlag;

	//  �L�����̌��݂̃X�s�[�h
	float charaSpeed;
	float mElapseTime;    // ���̃X�e�[�g�ɓ����Ă���̌o�ߎ���
	float mTotalAnimTime; // �A�j���[�V����������

	//����
	Vector3 dirVec;
	//�O�i����
	Vector3 forwardVec;
	//�E����
	Vector3 rightVec;
	// �L�����̑O�i�x�N�g��
	Vector3 charaForwardVec;
};