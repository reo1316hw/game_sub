#pragma once

class DashAttackEffect;

/// <summary>
/// �_�b�V���U��
/// </summary>
class PlayerObjectStateDashAttack : public PlayerObjectStateBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerObjectStateDashAttack();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerObjectStateDashAttack() {};

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	/// <returns> �v���C���[�̏�� </returns>
	PlayerState Update(PlayerObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// ���͏���
	/// </summary>
	/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
	/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
	void Input(PlayerObject* _owner, const InputState& _KeyState)override;

	/// <summary>
	/// �v���C���[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
	/// </summary>
	/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void Enter(PlayerObject* _owner, const float _DeltaTime)override;

	/// <summary>
    /// �q�b�g�������̏���
    /// </summary>
    /// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
    /// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
	void OnCollision(PlayerObject* _owner, const GameObject& _HitObject)override;

private:

	// �����蔻���L���ɂ���^�C�~���O
	const int MBoxEnableTiming;
	// �����蔻��𖳌��ɂ���^�C�~���O
	const int MBoxDisableTiming;
	// �G�l�~�[�̍U���̃_���[�W�l
	const int MDamageValueEnemyAttack;
	// �q�b�g�X�g�b�v���I���^�C�~���O
	const int MHitStopEndTiming;
	// �U�����̑��x
	const float MAttackSpeed;
	// �A�j���[�V�����̍Đ����x
	const float MPlayRate;

	// �R���{�L���t���[��
	const size_t MValidComboFrame;

	// �����蔻��̏��
	// true : �L��, false : ����
	bool mIsCollisionState;
	// �q�b�g�X�g�b�v���邩
	bool mIsHitStop;

	// �_���[�W�l
	int mDamageValue;
	// �����蔻�肷��܂ł̃J�E���g
	int mHitUntilCount;
	// �q�b�g�X�g�b�v����t���[����
	int mHitStopCount;

	// �t���[����
	size_t mNumFrame;

	// ���W
	Vector3 mPosition;
	// ���x
	Vector3 mVelocity;
	// �O���x�N�g��
	Vector3 mForwardVec;

	// �X�P���g���N���X�̃|�C���^
	SkeletalMeshComponent* skeletalMeshCompPtr;
	// �_�b�V���U���G�t�F�N�g�̃N���X�̃|�C���^
	DashAttackEffect* mDashAttackEffectPtr;

public:// �Q�b�^�[�Z�b�^�[

	/// <summary>
	/// �����蔻��̏�Ԃ��擾
	/// </summary>
	/// <returns> �����蔻��̏�� </returns>
	bool GetIsCollisionState() { return mIsCollisionState; }

	/// <summary>
	/// �_�b�V���U���G�t�F�N�g�̃N���X�̃|�C���^��ݒ�
	/// </summary>
	/// <param name="_thirdAttackEffectPtr"> �_�b�V���U���G�t�F�N�g�̃N���X�̃|�C���^ </param>
	void SetDashAttackEffectPtr(DashAttackEffect* _dashAttackEffectPtr) { mDashAttackEffectPtr = _dashAttackEffectPtr; }
};