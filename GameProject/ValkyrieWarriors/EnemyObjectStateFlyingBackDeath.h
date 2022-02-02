#pragma once

// �O���錾
class EnemyHitPointGauge;
class EnemyHitPointFrame;

/// <summary>
/// �G�l�~�[�̎��S���(�����ɔ�s���ė�����)
/// </summary>
class EnemyObjectStateFlyingBackDeath : public EnemyObjectStateBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
    /// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	EnemyObjectStateFlyingBackDeath(PlayerObject* _playerPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyObjectStateFlyingBackDeath() {};

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
	/// �q�b�g�������̏���
	/// </summary>
	/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
	/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
	void OnCollision(EnemyObject* _owner, const GameObject& _HitObject)override;

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
	ParticleGauge* mEnemyHitPointGaugePtr;
	// �G�l�~�[��hp�̘g�̃|�C���^
	ParticleFrame* mEnemyHitPointFramePtr;
};