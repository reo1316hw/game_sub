#pragma once

/// <summary>
/// �ړ����
/// </summary>
class EnemyObjectStateMove : public EnemyObjectStateBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	EnemyObjectStateMove(PlayerObject* _playerPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyObjectStateMove() {};

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

	/// <summary>
	/// �q�b�g���ꂽ���̏���
	/// </summary>
	/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
	void OnColision(const GameObject& _HitObject)override;

private:

	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void MoveCalc(EnemyObject* _owner, const float _DeltaTime);

	// �J�ڂ���^�C�~���O
	const int MTransitionTimingNum;

	// �ړ����Ă��邩
	bool mIsMoving;
	// �_���[�W���󂯂���
	bool mIsDamage;

	// �ړ����鎞�Ԃ̃J�E���g�ϐ�
	int mPeriodMoveCount;

	// �ړ����x
	float mMoveSpeed;

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
};