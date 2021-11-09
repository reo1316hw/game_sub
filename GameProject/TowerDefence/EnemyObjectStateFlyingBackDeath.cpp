#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
EnemyObjectStateFlyingBackDeath::EnemyObjectStateFlyingBackDeath(PlayerObject* _playerPtr)
	: MHitStopEndTiming(10)
	, MPlayRate(1.5f)
	, MDeathInitSpeed(0.0f)
	, MDecelerationSpeedValue(0.0f)
	, mIsHitStop(false)
	, mHitStopCount(0)
	, mDeathSpeed(0.0f)
	, mDecelerationSpeed(0.0f)
	, mPosition(Vector3::Zero)
	, mInitPosition(Vector3::Zero)
	, mDirPlayerVec(Vector3::Zero)
	, mPlayerPtr(_playerPtr)
	, mEnemyHitPointGaugePtr(nullptr)
	, mEnemyHitPointFramePtr(nullptr)
	, mBoxColliderPtr(nullptr)
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
/// <returns> �G�l�~�[�̏�� </returns>
EnemyState EnemyObjectStateFlyingBackDeath::Update(EnemyObject* _owner, const float _DeltaTime)
{
	++mHitStopCount;

	if (mHitStopCount <= MHitStopEndTiming)
	{
		return EnemyState::eEnemyStateFlyingBackDeath;
	}

	// ���x
	Vector3 velocity = mDeathSpeed * mDirPlayerVec;
	mDeathSpeed -= mDecelerationSpeed;
	mDecelerationSpeed += 0.05f;

	if (mDeathSpeed <= 0.0f)
	{
		mDeathSpeed = 0.0f;
	}

	mPosition -= velocity * _DeltaTime;

	_owner->SetPosition(mPosition);

	// �A�j���[�V�������I��������X�V���~�߂�
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		// hp�Q�[�W
		mEnemyHitPointGaugePtr = _owner->GetEnemyHitPointGaugePtr();
		// hp�̘g
		//mEnemyHitPointFramePtr = _owner->GetEnemyHitPointFramePtr();

		mEnemyHitPointGaugePtr->SetState(State::eDead);
		//mEnemyHitPointFramePtr->SetState(State::eDead);
		_owner->SetHitPoint(_owner->GetMaxHp());
		_owner->SetState(State::eDead);
		_owner->SetPosition(mInitPosition);

		return EnemyState::eEnemyStateTrack;
	}

	return EnemyState::eEnemyStateFlyingBackDeath;
}

/// <summary>
/// �G�l�~�[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void EnemyObjectStateFlyingBackDeath::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	mBoxColliderPtr = _owner->GetBoxCollider();
	// �G�l�~�[�̓����蔻��𖳌��ɂ���
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	mIsHitStop = false;

	// �v���C���[�̃X�e�[�g��3�i�K�ڂ̒ʏ�U����Ԃ�������q�b�g�X�g�b�v���s��
	if (mPlayerPtr->GetPlayerState() == PlayerState::ePlayerStateThirdAttack)
	{
		mIsHitStop = true;
	}

	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateFlyingBackDeath), MPlayRate);
	meshcomp->SetIsHitStop(mIsHitStop);

	// �q�b�g�X�g�b�v����t���[������������
	mHitStopCount = 0;

	// ���W
	mPosition = _owner->GetPosition();
	// �������W
	mInitPosition = _owner->GetInitPosition();
	// �v���C���[�̍��W
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// �v���C���[�Ɍ������x�N�g��
	mDirPlayerVec = playerPos - mPosition;
	mDirPlayerVec.Normalize();

	mDeathSpeed = 400.0f;
	mDecelerationSpeed = 1.8f;

	_owner->RotateToNewForward(mDirPlayerVec);
}

/// <summary>
/// �G�l�~�[�̏�Ԃ��ύX���āA�Ō��1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void EnemyObjectStateFlyingBackDeath::Exit(EnemyObject* _owner, const float _DeltaTime)
{
	// �G�l�~�[�̓����蔻���L���ɂ���
	mBoxColliderPtr->SetCollisionState(CollisionState::eEnableCollision);
}