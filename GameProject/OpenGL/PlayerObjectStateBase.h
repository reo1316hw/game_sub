#pragma once

// �O���錾
class AttackMeshComponent;

class PlayerObjectStateBase
{
public:

	PlayerObjectStateBase();

	virtual ~PlayerObjectStateBase() {};

	virtual PlayerState Update(class PlayerObject* _owner, float _deltaTime) = 0;

	virtual void Input(class PlayerObject* _owner, const InputState& _keyState) {};

	virtual void Enter(class PlayerObject* _owner, float _deltaTime) = 0;

	virtual void Exit(class PlayerObject* _owner, float _deltaTime) {};

protected:

	// ���̃R���{�ɂȂ��邩
	bool  mNextComboFlag;
	// �ҋ@���邩
	bool  mIdleFlag;
	// �����Ă��邩
	bool  mRunFlag;
	// �S�͎����n�߂�
	bool  mSprintStartFlag;
	// �S�͎������邩
	bool  mSprintFlag;
	// �U�����邩
	bool  mAttackFlag;

	// gpSkel�t�@�C���̉��Ԗڂ̃{�[����
	int	mAttackBoneIndex;

	// ���̃X�e�[�g�ɓ����Ă���̌o�ߎ���
	float mElapseTime;
	// �A�j���[�V����������
	float mTotalAnimTime;
	// �L�����̌��݂̃X�s�[�h
	float mCharaSpeed;

	//����
	Vector3 mDirVec;
	//�O�i����
	Vector3 mForwardVec;
	//�E����
	Vector3 mRightVec;
	// �L�����̑O�i�x�N�g��
	Vector3 mCharaForwardVec;

	//���탁�b�V���̃|�C���^
	AttackMeshComponent* mAttackMeshComponent;

private:
};