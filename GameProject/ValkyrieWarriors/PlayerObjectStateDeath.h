#pragma once

class PlayerObjectStateDeath : public PlayerObjectStateBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerObjectStateDeath();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerObjectStateDeath() {};

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

	// �X�V����߂邩
	bool mIsDead;

public:// �Q�b�^�[�Z�b�^�[

	/// <summary>
	/// �X�V����߂邩�̃t���O���擾
	/// </summary>
	/// <returns> �X�V����߂邩�̃t���O </returns>
	bool GetIsDead() { return mIsDead; }
};