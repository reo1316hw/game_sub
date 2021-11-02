#pragma once

/// <summary>
/// �G�l�~�[�̈ړ����
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
	/// �U�����󂯂����̏���
	/// </summary>
	/// <param name="_HitTag"> �q�b�g�����I�u�W�F�N�g�̃^�O </param>
	/// <param name="_DamageValuePlayerAttack"> �_���[�W�� </param>
	/// <returns> �q�b�g������ </returns>
	bool ReceivedAttack(const Tag& _HitTag, const int& _DamageValuePlayerAttack);

	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void MoveCalc(EnemyObject* _owner, const float _DeltaTime);

	// �q�b�g����I�u�W�F�N�g�̃��X�g
	Tag mHitTagList[4];

	// �J�ڂ���^�C�~���O
	const int MTransitionTimingNum;
	// ��ԑJ�ڊm��
	const int MStateTransitionProbability;
	// �v���C���[��1�i�K�ڂ̒ʏ�U���̃_���[�W�l
	const int MDamageValuePlayerFirstAttack;
	// ��Ԃ�ς��邽�߂̋���(�ߋ���)
	const float MTransitionStateShortDistance;
	// ��Ԃ�ς��邽�߂̋���(������)
	const float MTransitionStateMediumDistance;
	// �x�N�g����Z������l
	const float MVecShortenVelue;
	// ���������x�N�g���̒���
	const float MSeparationVecLength;

	// �ړ����Ă��邩
	bool mIsMoving;
	// �_���[�W���󂯂���
	bool mIsDamage;

	// �_���[�W�l
	int mDamageValue;
	// �ړ����鎞�Ԃ̃J�E���g�ϐ�
	int mPeriodMoveCount;
	// �q�b�g���鑊��̃��X�g�̗v�f��
	int mHitTagListSize;

	// �ړ����x
	float mMoveSpeed;

	// ���W
	Vector3 mPosition;
	// ���x
	Vector3 mVelocity;
	// �q�b�g�����I�u�W�F�N�g�̃^�O
	Tag mHitTag;
	// �G�l�~�[�̏��
	EnemyState mEnemyState;

	// �G�l�~�[�̃|�C���^
	EnemyObject* mEnemyPtr;
	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
};