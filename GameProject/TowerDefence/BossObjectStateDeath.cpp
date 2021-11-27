#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
BossObjectStateDeath::BossObjectStateDeath(PlayerObject* _playerPtr)
	: MMovingTiming(100)
	, MDamageSpeed(50.0f)
	, MVecShortenVelue(0.1f)
	, MSeparationVecLength(4.0f)
	, mMoveUntilCount(0)
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
BossState BossObjectStateDeath::Update(BossObject* _owner, const float _DeltaTime)
{
	++mMoveUntilCount;

	if (mMoveUntilCount >= MMovingTiming)
	{
		// �J�n���x
		float startSpeed = -MDamageSpeed * _DeltaTime;
		// �I�����x
		float endSpeed = MDamageSpeed * _DeltaTime;

		// �U�����ݍ��݈ړ��̂��߂̃A�j���[�V�����Đ����Ԃ̌o�ߊ������v�Z
		mElapseTime += _DeltaTime;
		// �o�ߊ��������ƂɈړ�����
		mPosition += Quintic::EaseIn(mElapseTime, startSpeed, endSpeed, mTotalAnimTime) * mDirPlayerVec;

		_owner->SetPosition(mPosition);
	}

	// �A�j���[�V�������I��������ҋ@��Ԃ�
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		_owner->SetState(State::eDead);
	}

	return BossState::eBossStateDeath;
}

/// <summary>
/// �{�X�ƃG�l�~�[�̈�������
/// </summary>
/// <param name="_owner"> �{�X�e)�̃|�C���^ </param>
/// <param name="_DirTargetEnemyVec"> �ΏۂƂȂ�G�l�~�[�Ɍ������x�N�g�� </param>
void BossObjectStateDeath::Separation(BossObject* _owner, const Vector3& _DirTargetEnemyVec)
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
void BossObjectStateDeath::Enter(BossObject* _owner, const float _DeltaTime)
{
	// �{�b�N�X�̓����蔻����s���R���|�[�l���g�N���X�̃|�C���^
	BoxCollider* boxColliderPtr = _owner->GetBoxCollider();
	// �G�l�~�[�̓����蔻��𖳌��ɂ���
	boxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(BossState::eBossStateDeath));

	// �A�j���[�V�����Đ����Ԏ擾
	mTotalAnimTime = _owner->GetAnimPtr(BossState::eBossStateDeath)->GetDuration()- 1.5f;
	mElapseTime = 0.0f;
	mMoveUntilCount = 0;

	// ���W
	mPosition = _owner->GetPosition();
	// �v���C���[�̍��W
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// �v���C���[�Ɍ������x�N�g��
	mDirPlayerVec = playerPos - mPosition;
	mDirPlayerVec.Normalize();

	_owner->RotateToNewForward(mDirPlayerVec);
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void BossObjectStateDeath::OnCollision(BossObject* _owner, const GameObject& _HitObject)
{
	// ���W
	mPosition = _owner->GetPosition();
}