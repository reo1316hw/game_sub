#pragma once
#include "PlayerObject.h"

class InputSystem;
class AttackMeshComponent;

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
	bool  mNextComboFlag;			//���̃R���{�ɂȂ��邩  
	bool  mIdleFlag;				//�ҋ@���邩
	bool  mRunStartFlag;			//����n�߂�
	bool  mRunFlag;					//�����Ă��邩
	bool  mSprintFlag;				//�S�͎������邩
	bool  mAttackFlag;				//�U�����邩
	bool  mDrawnSwordFlag;			//�������邩
	bool  mSwordDeliveryFlag;		//�[�����邩

	int	mAttackBoneIndex;  //gpSkel�t�@�C���̉��Ԗڂ̃{�[����

	float mElapseTime;    // ���̃X�e�[�g�ɓ����Ă���̌o�ߎ���
	float mTotalAnimTime; // �A�j���[�V����������
	float mCharaSpeed;	  // �L�����̌��݂̃X�s�[�h

	AttackMeshComponent* mAttackMeshComponent;	//���탁�b�V���̃|�C���^

	//����
	Vector3 mDirVec;
	//�O�i����
	Vector3 mForwardVec;
	//�E����
	Vector3 mRightVec;
	// �L�����̑O�i�x�N�g��
	Vector3 mCharaForwardVec;

	Vector3 mDrawnSwordRot; //�������̌��̉~����
	Vector3 mDrawnSwordPos; //�������̌��̍��W
	Vector3 mSwordDeliveryRot; //�[�����̌��̉~����
	Vector3 mSwordDeliveryPos; //�[�����̌��̍��W
private:
};