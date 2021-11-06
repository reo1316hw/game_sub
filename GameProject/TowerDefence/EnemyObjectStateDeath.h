#pragma once

// �O���錾
class EnemyHitPointGauge;
class EnemyHitPointFrame;

/// <summary>
/// �G�l�~�[�̎��S���
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

	/// <summary>
	/// �G�l�~�[�̏�Ԃ��ύX���āA�Ō��1�񂾂��Ăяo�����֐�
	/// </summary>
	/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void Exit(EnemyObject* _owner, const float _DeltaTime)override;

private:

	// �q�b�g�X�g�b�v���I���^�C�~���O
	const int MHitStopEndTiming;
	// �A�j���[�V�����̍Đ����x
	const float MPlayRate;
	// ���S���̏������x
	const float MDeathInitSpeed;
	// �����l
	const float MDecelerationSpeedValue;

	// �q�b�g�X�g�b�v���邩
	bool mIsHitStop;

	// �q�b�g�X�g�b�v����t���[����
	int mHitStopCount;

	// ���S���̑��x
	float mDeathSpeed;
	// �����x
	float mDecelerationSpeed;

	// ���W
	Vector3 mPosition;
	// �������W
	Vector3 mInitPosition;
	// �v���C���[�Ɍ������x�N�g��
	Vector3 mDirPlayerVec;

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
	// �G�l�~�[��hp�Q�[�W�̃|�C���^
	EnemyHitPointGauge* mEnemyHitPointGaugePtr;
	// �G�l�~�[��hp�̘g�̃|�C���^
	EnemyHitPointFrame* mEnemyHitPointFramePtr;
	// �{�b�N�X�̓����蔻����s���R���|�[�l���g�N���X�̃|�C���^
	BoxCollider* mBoxColliderPtr;
};