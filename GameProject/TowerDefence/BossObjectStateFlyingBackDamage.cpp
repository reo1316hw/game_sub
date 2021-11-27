#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
BossObjectStateFlyingBackDamage::BossObjectStateFlyingBackDamage(PlayerObject* _playerPtr)
	: MHitStopEndTiming(10)
	, MVecShortenVelue(0.1f)
	, MSeparationVecLength(4.0f)
	, MPlayRate(1.5f)
	, MDamageInitSpeed(400.0f)
	, MDecelerationSpeedValue(1.8f)
	, mIsHitStop(false)
	, mHitPoint(0)
	, mHitStopCount(0)
	, mDamageSpeed(0.0f)
	, mDecelerationSpeed(0.0f)
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
	, mDirPlayerVec(Vector3::Zero)
	, mPlayerPtr(_playerPtr)
	, mBoxColliderPtr(nullptr)
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
/// <returns> �{�X�̏�� </returns>
BossState BossObjectStateFlyingBackDamage::Update(BossObject* _owner, const float _DeltaTime)
{
	if (mHitPoint <= 0)
	{
		return BossState::eBossStateDeath;
	}

	++mHitStopCount;

	if (mHitStopCount <= MHitStopEndTiming)
	{
		return BossState::eBossStateFlyingBackDamage;
	}

	// ���x
	Vector3 velocity = mDamageSpeed * mDirPlayerVec;
	mDamageSpeed -= mDecelerationSpeed;
	mDecelerationSpeed += 0.05f;

	if (mDamageSpeed <= 0.0f)
	{
		mDamageSpeed = 0.0f;
	}

	mPosition -= velocity * _DeltaTime;

	_owner->SetPosition(mPosition);

	// �A�j���[�V�������I��������ҋ@��Ԃ�
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		return BossState::eBossStateTeleportation;
	}

	return BossState::eBossStateFlyingBackDamage;
}

/// <summary>
/// �{�X���m�̈�������
/// </summary>
/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
/// <param name="_DirTargetEnemyVec"> �ΏۂƂȂ�G�l�~�[�Ɍ������x�N�g�� </param>
void BossObjectStateFlyingBackDamage::Separation(BossObject* _owner, const Vector3& _DirTargetEnemyVec)
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
/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void BossObjectStateFlyingBackDamage::Enter(BossObject* _owner, const float _DeltaTime)
{
	mBoxColliderPtr = _owner->GetBoxCollider();
	// �G�l�~�[�̓����蔻��𖳌��ɂ���
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	mIsHitStop = false;

	// �v���C���[�̃X�e�[�g��3�i�K�ڂ̒ʏ�U����Ԃ�������q�b�g�X�g�b�v���s��
	if (mPlayerPtr->GetNowState() == PlayerState::ePlayerStateThirdAttack)
	{
		mIsHitStop = true;
	}

	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(BossState::eBossStateFlyingBackDamage), MPlayRate);
	meshcomp->SetIsHitStop(mIsHitStop);

	// �q�b�g�X�g�b�v����t���[������������
	mHitStopCount = 0;

	// ���W
	mPosition = _owner->GetPosition();
	// �v���C���[�̍��W
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// �v���C���[�Ɍ������x�N�g��
	mDirPlayerVec = playerPos - mPosition;
	mDirPlayerVec.Normalize();

	mDamageSpeed = MDamageInitSpeed;
	mDecelerationSpeed = MDecelerationSpeedValue;

	// �_���[�W�l
	int damageValue = _owner->GetDamageValue();
	// �̗�
	mHitPoint = _owner->GetHitPoint() - damageValue;

	// �I�u�W�F�N�g�̃X�P�[���T�C�Y�����߂邽�߂̍��ӂ̒l��ݒ�
	_owner->SetScaleLeftSideValue(mHitPoint);
	_owner->RotateToNewForward(mDirPlayerVec);
	_owner->SetHitPoint(mHitPoint);
}

/// <summary>
/// �{�X�̏�Ԃ��ύX���āA�Ō��1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void BossObjectStateFlyingBackDamage::Exit(BossObject* _owner, const float _DeltaTime)
{
	// �G�l�~�[�̓����蔻���L���ɂ���
	mBoxColliderPtr->SetCollisionState(CollisionState::eEnableCollision);
}