#pragma once

// �O���錾
class AttackMeshComponent;

/// <summary>
/// �v���C���[�X�e�[�g�̊��N���X
/// </summary>
class PlayerObjectStateBase
{
public:

	/// <summary>
    /// �R���X�g���N�^
    /// </summary>
	PlayerObjectStateBase();

	/// <summary>
    /// �f�X�g���N�^
    /// </summary>
	virtual ~PlayerObjectStateBase() {};

	/// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
    /// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
    /// <returns> �v���C���[�̏�� </returns>
	virtual PlayerState Update(PlayerObject* _owner, const float _DeltaTime) = 0;

	/// <summary>
	/// ���͏���
	/// </summary>
	/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
	/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
	virtual void Input(PlayerObject* _owner, const InputState& _KeyState) {};

	/// <summary>
	/// �v���C���[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
	/// </summary>
	/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	virtual void Enter(PlayerObject* _owner, const float _DeltaTime) = 0;

	/// <summary>
    /// �v���C���[�̏�Ԃ��ύX���āA�Ō��1�񂾂��Ăяo�����֐�
    /// </summary>
    /// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
    /// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	virtual void Exit(PlayerObject* _owner, const float _DeltaTime) {};

	/// <summary>
    /// �q�b�g�������̏���
    /// </summary>
    /// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
    /// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
	virtual void OnCollision(PlayerObject* _owner, const GameObject& _HitObject) {};

protected:

	// ���̃R���{�ɂȂ��邩
	bool mIsNextCombo;
	// �ҋ@���邩
	bool mIsIdle;
	// �����Ă��邩
	bool mIsRun;
	// �S�͎������邩
	bool mIsSprint;
	// �U�����邩
	bool mIsAttack;
	// ����������
	bool mIsHit;

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