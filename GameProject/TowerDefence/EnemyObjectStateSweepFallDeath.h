#pragma once

/// <summary>
/// �G�l�~�[�̎��S���(�������ŗ�����)
/// </summary>
class EnemyObjectStateSweepFallDeath : public EnemyObjectStateBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	EnemyObjectStateSweepFallDeath(PlayerObject* _playerPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyObjectStateSweepFallDeath() {};

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
	/// �G�l�~�[�̏�Ԃ��ύX���āA�Ō��1�񂾂��Ăяo�����֐�
	/// </summary>
	/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void Exit(EnemyObject* _owner, const float _DeltaTime)override;

private:

	// �x�N�g����Z������l
	const float MVecShortenVelue;
	// ���������x�N�g���̒���
	const float MSeparationVecLength;
	// ���S���̏����x
	const float MDeathInitSpeed;
	// �d��
	const float MGravity;

	// �̗�
	int mHitPoint;

	// ���S���̑��x
	float mDeathSpeed;

	// ���W
	Vector3 mPosition;
	// �������W
	Vector3 mInitPosition;
	// ���̃X�e�[�g�ɓ��������̍��W
	Vector3 mNowStateInitPos;
	// ���x
	Vector3 mVelocity;
	// �v���C���[�Ɍ������x�N�g��
	Vector3 mDirPlayerVec;

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
	// �G�l�~�[��hp�Q�[�W�̃|�C���^
	ParticleGauge* mEnemyHitPointGaugePtr;
	// �G�l�~�[��hp�̘g�̃|�C���^
	ParticleFrame* mEnemyHitPointFramePtr;
	// �{�b�N�X�̓����蔻����s���R���|�[�l���g�N���X�̃|�C���^
	BoxCollider* mBoxColliderPtr;
};