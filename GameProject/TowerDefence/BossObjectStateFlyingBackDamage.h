#pragma once

/// <summary>
/// �{�X���_���[�W���󂯂����(�����܂Ŕ�s���ė�����)
/// </summary>
class BossObjectStateFlyingBackDamage : public BossObjectStateBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	BossObjectStateFlyingBackDamage(PlayerObject* _playerPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BossObjectStateFlyingBackDamage() {};

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	/// <returns> �{�X�̏�� </returns>
	BossState Update(BossObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// �{�X�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
	/// </summary>
	/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void Enter(BossObject* _owner, const float _DeltaTime)override;

	/// <summary>
    /// �{�X�̏�Ԃ��ύX���āA�Ō��1�񂾂��Ăяo�����֐�
    /// </summary>
    /// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
    /// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void Exit(BossObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// �{�X���m�̈�������
	/// </summary>
	/// <param name="_owner"> �{�X�e)�̃|�C���^ </param>
	/// <param name="_DirTargetEnemyVec"> �ΏۂƂȂ�G�l�~�[�Ɍ������x�N�g�� </param>
	void Separation(BossObject* _owner, const Vector3& _DirTargetEnemyVec)override;

private:

	// �q�b�g�X�g�b�v���I���^�C�~���O
	const int MHitStopEndTiming;
	// �x�N�g����Z������l
	const float MVecShortenVelue;
	// ���������x�N�g���̒���
	const float MSeparationVecLength;
	// �A�j���[�V�����̍Đ����x
	const float MPlayRate;
	// �_���[�W���̏������x
	const float MDamageInitSpeed;
	// �����l
	const float MDecelerationSpeedValue;

	// �q�b�g�X�g�b�v���邩
	bool mIsHitStop;

	// �̗�
	int mHitPoint;
	// �q�b�g�X�g�b�v����t���[����
	int mHitStopCount;

	// ���S���̑��x
	float mDamageSpeed;
	// �����x
	float mDecelerationSpeed;

	// ���W
	Vector3 mPosition;
	// ���x
	Vector3 mVelocity;
	// �v���C���[�Ɍ������x�N�g��
	Vector3 mDirPlayerVec;

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
	// �{�b�N�X�̓����蔻����s���R���|�[�l���g�N���X�̃|�C���^
	BoxCollider* mBoxColliderPtr;
};