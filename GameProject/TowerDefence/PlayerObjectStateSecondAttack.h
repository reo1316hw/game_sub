#pragma once

/// <summary>
/// 2�i�K�ڂ̍U��
/// </summary>
class PlayerObjectStateSecondAttack : public PlayerObjectStateBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerObjectStateSecondAttack(PlayerWeaponObject* _weaponPtr);

	/// <summary>
    /// �f�X�g���N�^
    /// </summary>
	~PlayerObjectStateSecondAttack() {};

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
	/// �v���C���[�̏�Ԃ��ύX���āA�Ō��1�񂾂��Ăяo�����֐�
	/// </summary>
	/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void Exit(PlayerObject* _owner, const float _DeltaTime)override;

private:

	// �����蔻���L���ɂ���^�C�~���O
	const int MBoxEnableTiming;
	// �U�����̑��x
	const float MAttackSpeed;
	// �A�j���[�V�����̍Đ����x
	const float MPlayRate;

	// �R���{�L���t���[��
	const size_t MValidComboFrame;

	// �����蔻�肷��܂ł̃J�E���g
	int mHitUntilCount;
	// �t���[����
	size_t mNumFrame;

	// �v���C���[����̃|�C���^
	PlayerWeaponObject* mWeaponPtr;
};