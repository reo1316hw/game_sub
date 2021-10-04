#pragma once

/// <summary>
/// 3�i�K�ڂ̍U��
/// </summary>
class PlayerObjectStateThirdAttack : public PlayerObjectStateBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerObjectStateThirdAttack();

	/// <summary>
    /// �f�X�g���N�^
    /// </summary>
	~PlayerObjectStateThirdAttack() {};

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	/// <returns> �v���C���[�̏�� </returns>
	PlayerState Update(PlayerObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// �v���C���[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
	/// </summary>
	/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void Enter(PlayerObject* _owner, const float _DeltaTime)override;

private:

	// �U�����̑��x
	const float MAttackSpeed;
	// �A�j���[�V�����̍Đ����x
	const float MPlayRate;
};