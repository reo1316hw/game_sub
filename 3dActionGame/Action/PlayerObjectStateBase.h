#pragma once
#include "PlayerObject.h"

class InputSystem;

class PlayerObjectStateBase
{
public:
	PlayerObjectStateBase();
	virtual ~PlayerObjectStateBase() {};
	virtual PlayerState Update(class PlayerObject* _owner, float _deltaTime) = 0;
	virtual void Inipt(class PlayerObject* _owner, const InputState& _keyState) = 0;
	virtual void Enter(class PlayerObject* _owner, float _deltaTime) {};
	virtual void Exit(class PlayerObject* _owner, float _deltaTime) {};
protected:
	////�����(�W�����v�p)
	//Vector3 jumpVec;
	//// �W�����v�X�s�[�h
	//const float JUMP_SPEED = 1000.0f;
	bool  mIsNextCombo;   // ���̃R���{�ɂȂ��邩  
	float mElapseTime;    // ���̃X�e�[�g�ɓ����Ă���̌o�ߎ���
	float mTotalAnimTime; // �A�j���[�V����������

	//  �L�����̌��݂̃X�s�[�h
	float mCharaSpeed;

	//����
	Vector3 mDirVec;
	//�O�i����
	Vector3 mForwardVec;
	//�E����
	Vector3 mRightVec;
	// �L�����̑O�i�x�N�g��
	Vector3 mCharaForwardVec;
private:
};