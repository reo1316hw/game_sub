#pragma once

/// <summary>
/// �S�͎������n�߂���
/// </summary>
class PlayerObjectStateSprintStart : public PlayerObjectStateBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerObjectStateSprintStart();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerObjectStateSprintStart() {};

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

	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void MoveCalc(PlayerObject* _owner, const float _DeltaTime);

	// �ړ����x
	const float MMoveSpeed;
	// �ő呬�x
	const float MMaxSpeed;
	// �A�j���[�V�����̍Đ����x
	const float MPlayRate;
	// �����̂������l
	const float MDirThreshold;
};