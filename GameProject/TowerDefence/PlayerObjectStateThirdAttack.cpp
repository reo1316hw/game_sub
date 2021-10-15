#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_weaponPtr"> �v���C���[�̕���̃|�C���^ </param>
PlayerObjectStateThirdAttack::PlayerObjectStateThirdAttack(PlayerWeaponObject* _weaponPtr)
	: MBoxEnableTiming(30)
	, MAttackSpeed(150.0f)
	, MPlayRate(1.5f)
	, mHitUntilCount(0)
	, mOwnerBoxCollider(_weaponPtr->GetBoxCollider())
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
/// <returns> �v���C���[�̏�� </returns>
PlayerState PlayerObjectStateThirdAttack::Update(PlayerObject* _owner, const float _DeltaTime)
{
	// ���W
	Vector3 pos = _owner->GetPosition();
	// �O���x�N�g��
	Vector3 forward = _owner->GetForward();
	// �J�n���x
	float startSpeed = MAttackSpeed * _DeltaTime;
	// �I�����x
	float endSpeed = -MAttackSpeed * _DeltaTime;

	// �U�����ݍ��݈ړ��̂��߂̃A�j���[�V�����Đ����Ԃ̌o�ߊ������v�Z
	mElapseTime += _DeltaTime;
	// �o�ߊ��������ƂɈړ�����
	pos += Quintic::EaseIn(mElapseTime, startSpeed, endSpeed, mTotalAnimTime) * forward;

	_owner->SetPosition(pos);

	++mHitUntilCount;

	if (mHitUntilCount == MBoxEnableTiming)
	{
		// ����̓����蔻����s���悤�ɂ���
		mOwnerBoxCollider->SetCollisionState(CollisionState::eEnableCollision);
	}

	// �A�j���[�V�������I��������cStopTime�d����AIDLE��Ԃ�
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		return PlayerState::ePlayerStateIdle;
	}
	else if (mIsHit)
	{
		return PlayerState::ePlayerStateDamage;
	}

	return PlayerState::ePlayerStateThirdAttack;
}

/// <summary>
/// �v���C���[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void PlayerObjectStateThirdAttack::Enter(PlayerObject* _owner, const float _DeltaTime)
{
	// ATTACK3�̃A�j���[�V�����Đ�
	SkeletalMeshComponent* meshComp = _owner->GetSkeletalMeshComponentPtr();
	meshComp->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateThirdAttack), MPlayRate);
	mIsHit = false;

	// �A�j���[�V�����Đ����Ԏ擾
	mTotalAnimTime = _owner->GetAnimPtr(PlayerState::ePlayerStateThirdAttack)->GetDuration() - 0.6f;
	mElapseTime = 0.0f;
	mHitUntilCount = 0;
}

/// <summary>
/// �v���C���[�̏�Ԃ��ύX���āA�Ō��1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void PlayerObjectStateThirdAttack::Exit(PlayerObject* _owner, const float _DeltaTime)
{
	// ����̓����蔻����s��Ȃ��悤�ɂ���
	mOwnerBoxCollider->SetCollisionState(CollisionState::eDisableCollision);
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void PlayerObjectStateThirdAttack::OnCollision(PlayerObject* _owner, const GameObject& _HitObject)
{
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eEnemyAttackDecision)
	{
		mIsHit = true;
	}
}