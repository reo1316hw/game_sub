#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
EnemyObjectStateSweepFallDeath::EnemyObjectStateSweepFallDeath(PlayerObject* _playerPtr)
	: MVecShortenVelue(0.1f)
	, MSeparationVecLength(4.0f)
	, MDeathInitSpeed(100.0f)
	, MGravity(4.0f)
	, mHitPoint(0)
	, mDeathSpeed(0.0f)
	, mPosition(Vector3::Zero)
	, mInitPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
	, mDirPlayerVec(Vector3::Zero)
	, mPlayerPtr(_playerPtr)
	, mEnemyHitPointGaugePtr(nullptr)
	, mEnemyHitPointFramePtr(nullptr)
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
/// <returns> �G�l�~�[�̏�� </returns>
EnemyState EnemyObjectStateSweepFallDeath::Update(EnemyObject* _owner, const float _DeltaTime)
{
	// ���x
	Vector3 velocity = mDeathSpeed * Vector3::UnitZ;
	mDeathSpeed -= MGravity;

	mPosition += velocity * _DeltaTime;

	if (mPosition.z <= mNowStateInitPos.z)
	{
		mPosition.z = mNowStateInitPos.z;
	}

	_owner->SetPosition(mPosition);

	// �A�j���[�V�������I��������X�V���~�߂�
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		// hp�Q�[�W
		mEnemyHitPointGaugePtr = _owner->GetEnemyHitPointGaugePtr();
		// hp�̘g
		mEnemyHitPointFramePtr = _owner->GetEnemyHitPointFramePtr();

		mEnemyHitPointGaugePtr->SetState(State::eDead);
		mEnemyHitPointFramePtr->SetState(State::eDead);

		_owner->SetHitPoint(_owner->GetMaxHp());
		_owner->SetScaleLeftSideValue(_owner->GetMaxHp());
		_owner->SetState(State::eDead);
		_owner->SetPosition(mInitPosition);

		return EnemyState::eEnemyStateTrack;
	}

	return EnemyState::eEnemyStateSweepFallDeath;
}

/// <summary>
/// �G�l�~�[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void EnemyObjectStateSweepFallDeath::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateSweepFallDeath));

	mDeathSpeed = MDeathInitSpeed;

	// ���W
	mPosition = _owner->GetPosition();
	// ���̃X�e�[�g�ɓ��������̍��W
	mNowStateInitPos = mPosition;
	// �������W
	mInitPosition = _owner->GetInitPosition();
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
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void EnemyObjectStateSweepFallDeath::OnCollision(EnemyObject* _owner, const GameObject& _HitObject)
{
	// ���W
	mPosition = _owner->GetPosition();
}