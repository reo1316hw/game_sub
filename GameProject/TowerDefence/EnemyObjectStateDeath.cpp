#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
EnemyObjectStateDeath::EnemyObjectStateDeath(PlayerObject* _playerPtr)
	: MHitStopEndTiming(10)
	, MPlayRate(1.5f)
	, MDecelerationSpeed(1.8f)
	, mIsHitStop(false)
	, mHitStopCount(0)
	, mDeathSpeed(200.0f)
	, mPlayerPtr(_playerPtr)
	, mPosition(Vector3::Zero)
	, mInitPosition(Vector3::Zero)
	, mDirPlayerVec(Vector3::Zero)
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
/// <returns> �G�l�~�[�̏�� </returns>
EnemyState EnemyObjectStateDeath::Update(EnemyObject* _owner, const float _DeltaTime)
{
	++mHitStopCount;

	if (mHitStopCount <= MHitStopEndTiming)
	{
		return EnemyState::eEnemyStateDeath;
	}

	// ���x
	Vector3 velocity = mDeathSpeed * mDirPlayerVec;
	mDeathSpeed -= MDecelerationSpeed;

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
		mEnemyHitPointFramePtr = _owner->GetEnemyHitPointFramePtr();

		mEnemyHitPointGaugePtr->SetState(State::eDead);
		mEnemyHitPointFramePtr->SetState(State::eDead);
		_owner->SetHitPoint(_owner->GetMaxHp());
		_owner->SetState(State::eDead);
		_owner->SetPosition(mInitPosition);

		return EnemyState::eEnemyStateTrack;
	}

	return EnemyState::eEnemyStateDeath;
}

/// <summary>
/// �G�l�~�[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void EnemyObjectStateDeath::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	mIsHitStop = false;

	if (mPlayerPtr->GetPlayerState() == PlayerState::ePlayerStateThirdAttack)
	{
		mIsHitStop = true;
	}

	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateDeath), MPlayRate);
	meshcomp->SetIsHitStop(mIsHitStop);

	// ���W
	mPosition = _owner->GetPosition();
	// �������W
	mInitPosition = _owner->GetInitPosition();
	// �v���C���[�̍��W
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// �v���C���[�Ɍ������x�N�g��
	mDirPlayerVec = playerPos - mPosition;
	mDirPlayerVec.Normalize();

	// �q�b�g�X�g�b�v����t���[������������
	mHitStopCount = 0;

	mDeathSpeed = 200.0f;

	_owner->RotateToNewForward(mDirPlayerVec);
}