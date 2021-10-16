#pragma once

/// <summary>
/// ���S���
/// </summary>
class EnemyObjectStateDeath : public EnemyObjectStateBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
    /// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	EnemyObjectStateDeath(PlayerObject* _playerPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyObjectStateDeath() {};

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	/// <returns> �G�l�~�[�̏�� </returns>
	EnemyState Update(EnemyObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// �G�l�~�[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
	/// </summary>
	/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void Enter(EnemyObject* _owner, const float _DeltaTime)override;

private:

	// �A�j���[�V�����̍Đ����x
	const float MPlayRate;
	// �����l
	const float MDecelerationSpeed;
	
		// ���S���̑��x
	float mDeathSpeed;

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;

	// ���W
	Vector3 mPosition;
	// �v���C���[�Ɍ������x�N�g��
	Vector3 mDirPlayerVec;
};