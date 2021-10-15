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
	/// <param name="_State"> �G�l�~�[�̏�� </param>
	/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	EnemyObjectStateMove(const EnemyState& _State, PlayerObject* _playerPtr);

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
	/// �G�l�~�[���m�̈�������
	/// </summary>
	/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
	/// <param name="_DirTargetEnemyVec"> �ΏۂƂȂ�G�l�~�[�Ɍ������x�N�g�� </param>
	void Separation(EnemyObject* _owner, const Vector3& _DirTargetEnemyVec)override;

	/// <summary>
	/// �q�b�g�������̏���
	/// </summary>
	/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
	/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
	void OnCollision(EnemyObject* _owner, const GameObject& _HitObject)override;

private:

	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void MoveCalc(EnemyObject* _owner, const float _DeltaTime);

	// �J�ڂ���^�C�~���O
	const int MTransitionTimingNum;
	// ��Ԃ�ς��邽�߂̋���
	const float MTransitionStateDistance;
	// �x�N�g����Z������l
	const float MVecShortenVelue;
	// ���������x�N�g���̒���
	const float MSeparationVecLength;

	// �ړ����Ă��邩
	bool mIsMoving;
	// �_���[�W���󂯂���
	bool mIsDamage;

	// �ړ����鎞�Ԃ̃J�E���g�ϐ�
	int mPeriodMoveCount;

	// �ړ����x
	float mMoveSpeed;

	// ���W
	Vector3 mPosition;
	// ���x
	Vector3 mVelocity;

	// �G�l�~�[�̏��
	EnemyState mEnemyState;

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
};