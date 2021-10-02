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
	PlayerObjectStateSecondAttack();

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

private:

	// �U�����̑��x
	const float MPlayerAttackSpeed;
	// �A�j���[�V�����̍Đ����x
	const float MPlayRate;

	// �R���{�L���t���[��
	const int MValidComboFrame;

	// �t���[����
	size_t mNumFrame;
};