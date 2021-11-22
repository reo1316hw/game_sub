#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
BossObjectStateDamage::BossObjectStateDamage(PlayerObject* _playerPtr)
	: MDamageSpeed(150.0f)
	, MVecShortenVelue(0.1f)
	, MSeparationVecLength(4.0f)
	, mIsHitStop(false)
	, mHitPoint(0)
	, mHitStopCount(0)
    , mHitStopEndTiming(0)
	, mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
	, mDirPlayerVec(Vector3::Zero)
	, mPlayerPtr(_playerPtr)
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
/// <returns> �{�X�̏�� </returns>
BossState BossObjectStateDamage::Update(BossObject* _owner, const float _DeltaTime)
{
	++mHitStopCount;

	if (mHitStopCount <= mHitStopEndTiming)
	{
		return BossState::eBossStateDamage;
	}

	// �J�n���x
	float startSpeed = -MDamageSpeed * _DeltaTime;
	// �I�����x
	float endSpeed = MDamageSpeed * _DeltaTime;

	// �U�����ݍ��݈ړ��̂��߂̃A�j���[�V�����Đ����Ԃ̌o�ߊ������v�Z
	mElapseTime += _DeltaTime;
	// �o�ߊ��������ƂɈړ�����
	mPosition += Quintic::EaseIn(mElapseTime, startSpeed, endSpeed, mTotalAnimTime) * mDirPlayerVec;

	_owner->SetPosition(mPosition);

	if (mHitPoint <= 0)
	{
		return BossState::eBossStateDeath;
	}

	// �A�j���[�V�������I��������ҋ@��Ԃ�
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		return BossState::eBossStateTeleportation;
	}

	return BossState::eBossStateDamage;
}

/// <summary>
/// �{�X�ƃG�l�~�[�̈�������
/// </summary>
/// <param name="_owner"> �{�X�e)�̃|�C���^ </param>
/// <param name="_DirTargetEnemyVec"> �ΏۂƂȂ�G�l�~�[�Ɍ������x�N�g�� </param>
void BossObjectStateDamage::Separation(BossObject* _owner, const Vector3& _DirTargetEnemyVec)
{
	// ���W
	mPosition = _owner->GetPosition();
	// ���������x�N�g��
	Vector3 separationVec = MSeparationVecLength * _DirTargetEnemyVec;

	mVelocity -= separationVec;
	mVelocity *= MVecShortenVelue;
	mPosition += mVelocity;

	_owner->SetPosition(mPosition);
}

/// <summary>
/// �{�X�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �{�X�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void BossObjectStateDamage::Enter(BossObject* _owner, const float _DeltaTime)
{
	mIsHitStop = false;

	// �v���C���[�̃X�e�[�g��3�i�K�ڂ̒ʏ�U����Ԃ�������q�b�g�X�g�b�v���s��
	if (mPlayerPtr->GetPlayerState() == PlayerState::ePlayerStateThirdAttack)
	{
		mHitStopEndTiming = 10;
		mIsHitStop = true;
	}

	// �v���C���[�̃X�e�[�g���_�b�V���U����Ԃ�������q�b�g�X�g�b�v���s��
	if (mPlayerPtr->GetPlayerState() == PlayerState::ePlayerStateDashAttack)
	{
		mHitStopEndTiming = 5;
		mIsHitStop = true;
	}

	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(BossState::eBossStateDamage), 1.5f, mHitStopEndTiming);
	meshcomp->SetIsHitStop(mIsHitStop);
	
	// �A�j���[�V�����Đ����Ԏ擾
	mTotalAnimTime = _owner->GetAnimPtr(BossState::eBossStateDamage)->GetDuration();
	mElapseTime = 0.0f;

	// �q�b�g�X�g�b�v����t���[������������
	mHitStopCount = 0;

	// ���W
	mPosition = _owner->GetPosition();
	// �v���C���[�̍��W
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// �v���C���[�Ɍ������x�N�g��
	mDirPlayerVec = playerPos - mPosition;
	mDirPlayerVec.Normalize();

	// �_���[�W�l
	int damageValue = _owner->GetDamageValue();
	// �̗�
	mHitPoint = _owner->GetHitPoint() - damageValue;

	// �I�u�W�F�N�g�̃X�P�[���T�C�Y�����߂邽�߂̍��ӂ̒l��ݒ�
	_owner->SetScaleLeftSideValue(mHitPoint);
	_owner->RotateToNewForward(mDirPlayerVec);
	_owner->SetHitPoint(mHitPoint);
}