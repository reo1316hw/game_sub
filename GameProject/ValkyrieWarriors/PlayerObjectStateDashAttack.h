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

	/// <summary>
	/// �U�����󂯂����̏���
	/// </summary>
	/// <param name="_HitTag"> �q�b�g�����I�u�W�F�N�g�̃^�O </param>
	/// <param name="_DamageValuePlayerAttack"> �_���[�W�� </param>
	/// <returns> �q�b�g������ </returns>
	bool ReceivedAttack(const Tag& _HitTag, const int& _DamageValuePlayerAttack);

	// �q�b�g����I�u�W�F�N�g�̃��X�g
	Tag mHitTagList[4];

	// �_���[�W�l�̃��X�g
	int mDamageValueList[4];

	// �q�b�g�X�g�b�v���I���^�C�~���O
	const int MHitStopEndTiming;
	// �����蔻���L���ɂ���^�C�~���O
	const float MBoxEnableTiming;
	// �U�����̑��x
	const float MAttackSpeed;
	// �A�j���[�V�����̍Đ����x
	const float MPlayRate;
	// �R���{�L���t���[��
	const float MValidComboFrame;

	// �����蔻��̏��
	// true : �L��, false : ����
	bool mIsCollisionState;
	// �q�b�g�X�g�b�v���邩
	bool mIsHitStop;
	// ���݂̃X�e�[�g�ɓ�����1�񂾂������蔻���L���ɂ���
	bool mIsOneCollisionState;

	// �_���[�W���󂯂���
	bool mIsDamage;

	// �_���[�W�l
	int mDamageValue;
	// �q�b�g���鑊��̃��X�g�̗v�f��
	int mHitTagListSize;
	// �q�b�g�X�g�b�v����t���[����
	int mHitStopCount;

	// �����蔻��𖳌��ɂ���^�C�~���O
	float mBoxDisableTiming;

	// ���W
	Vector3 mPosition;
	// ���x
	Vector3 mVelocity;
	// �O���x�N�g��
	Vector3 mForwardVec;

	// �q�b�g�����I�u�W�F�N�g�̃^�O
	Tag mHitTag;

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
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