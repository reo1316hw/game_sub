#pragma once

/// <summary>
/// 1�i�K�ڂ̍U��
/// </summary>
class PlayerObjectStateFirstAttack : public PlayerObjectStateBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerObjectStateFirstAttack();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerObjectStateFirstAttack() {};

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
	// �U�����̑��x
	const float MAttackSpeed;
	// �A�j���[�V�����̍Đ����x
	const float MPlayRate;
	//�ړ����邽�߂̍��X�e�B�b�N�̂������l
	const float MLeftAxisThreshold;
	// �R���{�L���t���[��
	const size_t MValidComboFrame;

	// �����蔻��̏��
	// true : �L��, false : ����
	bool mIsCollisionState;

	// ��]���邩
	bool mIsRotation;

	// �_���[�W�l
	int mDamageValue;
	// �����蔻�肷��܂ł̃J�E���g
	int mHitUntilCount;

	// �t���[����
	size_t mNumFrame;

	// ���X�e�B�b�N�̓��͒l(-1~1)
	Vector2 mleftAxis;
	// ���W
	Vector3 mPosition;
	// �O���x�N�g��
	Vector3 mForwardVec;

public:// �Q�b�^�[�Z�b�^�[

	/// <summary>
	/// �����蔻��̏�Ԃ��擾
	/// </summary>
	/// <returns> �����蔻��̏�� </returns>
	bool GetIsCollisionState() { return mIsCollisionState; }
};