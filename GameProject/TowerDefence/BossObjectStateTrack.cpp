#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
BossObjectStateTrack::BossObjectStateTrack(PlayerObject* _playerPtr)
	: MTimingTransitionOverheadAttack(240)
	, MTransitionStateDistance(30000.0f)
	, MVecShortenVelue(0.1f)
	, MSeparationVecLength(4.0f)
	, mIsDamage(false)
	, UntilTransitionOverheadAttackCount(0)
	, mMoveSpeed(5.0f)
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
	, mPlayerPtr(_playerPtr)
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
/// <returns> �{�X�̏�� </returns>
BossState BossObjectStateTrack::Update(BossObject* _owner, const float _DeltaTime)
{
	// �v���C���[�̍��W
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// �v���C���[�Ɍ������x�N�g��
	Vector3 dirPlayerVec = playerPos - mPosition;

	// �����_���l
	int randNum = rand() % 100;

	++UntilTransitionOverheadAttackCount;

	if (dirPlayerVec.LengthSq() < MTransitionStateDistance)
	{
		if (randNum < 20)
		{
			return BossState::eBossStateWait;
		}
		else if (randNum >= 20 && randNum < 40)
		{
			return BossState::eBossStateAreaAttack;
		}
		else if (randNum >= 40 && randNum < 60)
		{
			return BossState::eBossStateFrontAttack;
		}
		else if (randNum >= 60 && randNum < 80)
		{
			return BossState::eBossStateOverheadAttack;
		}
		else
		{
			return BossState::eBossStateTeleportation;
		}
	}
	else if(UntilTransitionOverheadAttackCount >= MTimingTransitionOverheadAttack)
	{
		if (randNum < 30)
		{
			return BossState::eBossStateOverheadAttack;
		}
		else if (randNum >= 30 && randNum < 60)
		{
			return BossState::eBossStateTeleportation;
		}
	}
	else if (mIsDamage)
	{
		return BossState::eBossStateDamage;
	}

	dirPlayerVec.Normalize();
	_owner->RotateToNewForward(dirPlayerVec);

	mVelocity = mMoveSpeed * dirPlayerVec;
	mPosition += mVelocity;
	// �L�����̈ʒu�E�X�s�[�h�E�ϊ��s��̍Čv�Z�̕K�v���Z�b�g
	_owner->SetPosition(mPosition);

	return BossState::eBossStateTrack;
}

/// <summary>
/// �{�X�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void BossObjectStateTrack::Enter(BossObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(BossState::eBossStateTrack));

	mIsDamage = false;
	UntilTransitionOverheadAttackCount = 0;

	// ���W
	mPosition = _owner->GetPosition();
}

/// <summary>
/// �{�X���m�̈�������
/// </summary>
/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
/// <param name="_DirTargetEnemyVec"> �ΏۂƂȂ�G�l�~�[�Ɍ������x�N�g�� </param>
void BossObjectStateTrack::Separation(BossObject* _owner, const Vector3& _DirTargetEnemyVec)
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
/// �q�b�g�������̏���
/// </summary>
/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void BossObjectStateTrack::OnCollision(BossObject* _owner, const GameObject& _HitObject)
{
	// ���W
	mPosition = _owner->GetPosition();

	// �I�u�W�F�N�g�̃^�O
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eWeapon)
	{
		mIsDamage = true;
	}
}