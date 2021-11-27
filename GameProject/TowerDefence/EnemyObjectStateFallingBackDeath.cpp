#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
EnemyObjectStateFallingBackDeath::EnemyObjectStateFallingBackDeath(PlayerObject* _playerPtr)
	: MDamageSpeed(50.0f)
	, mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
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
EnemyState EnemyObjectStateFallingBackDeath::Update(EnemyObject* _owner, const float _DeltaTime)
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

	// �A�j���[�V�������I��������ҋ@��Ԃ�
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

	return EnemyState::eEnemyStateFallingBackDeath;
}

/// <summary>
/// �G�l�~�[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void EnemyObjectStateFallingBackDeath::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateFallingBackDeath));

	// �A�j���[�V�����Đ����Ԏ擾
	mTotalAnimTime = _owner->GetAnimPtr(EnemyState::eEnemyStateFallingBackDeath)->GetDuration() - 0.3f;
	mElapseTime = 0.0f;

	// ���W
	mPosition = _owner->GetPosition();
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
void EnemyObjectStateFallingBackDeath::OnCollision(EnemyObject* _owner, const GameObject& _HitObject)
{
	// ���W
	mPosition = _owner->GetPosition();
}