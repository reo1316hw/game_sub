#pragma once

class EnemyObjectStateFallingBackDeath : public EnemyObjectStateBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	EnemyObjectStateFallingBackDeath(PlayerObject* _playerPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyObjectStateFallingBackDeath() {};

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

	// �_���[�W���̑��x
	const float MDamageSpeed;
	// �A�j���[�V�����̍Đ����x
	const float MPlayRate;
	// �q�b�g�X�g�b�v���I���^�C�~���O
	const int MHitStopEndTiming;

	// �q�b�g�X�g�b�v���邩
	bool mIsHitStop;

	// �q�b�g�X�g�b�v����t���[����
	int mHitStopCount;

	// ���̃X�e�[�g�ɓ����Ă���̌o�ߎ���
	float mElapseTime;
	// �A�j���[�V����������
	float mTotalAnimTime;

	// ���W
	Vector3 mPosition;
	// �������W
	Vector3 mInitPosition;
	// ���x
	Vector3 mVelocity;
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