#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_weaponPtr"> �v���C���[�̕���̃|�C���^ </param>
PlayerObjectStateThirdAttack::PlayerObjectStateThirdAttack(PlayerWeaponObject* _weaponPtr)
	: MBoxEnableTiming(30)
	, MDamageValueEnemyAttack(25)
	, MHitStopEndTiming(10)
	, MAttackSpeed(150.0f)
	, MPlayRate(1.5f)
	, mIsHitStop(false)
	, mDamageValue(0)
	, mHitUntilCount(0)
	, mHitStopCount(0)
	, mPosition(Vector3::Zero)
	, mForwardVec(Vector3::Zero)
	, mOwnerBoxCollider(_weaponPtr->GetBoxCollider())
	, mWeaponPtr(_weaponPtr)
	, skeletalMeshCompPtr(nullptr)
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
	if (mIsHit)
	{
		return PlayerState::ePlayerStateDamage;
	}

	// �U�����ɕ��킪����������q�b�g�X�g�b�v���s��
	if (mWeaponPtr->IsHitCheck())
	{
		mIsHitStop = true;
		skeletalMeshCompPtr->SetIsHitStop(mIsHitStop);
	}

	// �q�b�g�X�g�b�v���Ɉړ������𖳌���
	if (mIsHitStop)
	{
		++mHitStopCount;

		if (mHitStopCount <= MHitStopEndTiming)
		{
			return PlayerState::ePlayerStateThirdAttack;
		}

		mIsHitStop = false;
		mHitStopCount = 0;
	}

	// �J�n���x
	float startSpeed = MAttackSpeed * _DeltaTime;
	// �I�����x
	float endSpeed = -MAttackSpeed * _DeltaTime;

	// �U�����ݍ��݈ړ��̂��߂̃A�j���[�V�����Đ����Ԃ̌o�ߊ������v�Z
	mElapseTime += _DeltaTime;
	// �o�ߊ��������ƂɈړ�����
	mPosition += Quintic::EaseIn(mElapseTime, startSpeed, endSpeed, mTotalAnimTime) * mForwardVec;

	_owner->SetPosition(mPosition);

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

	return PlayerState::ePlayerStateThirdAttack;
}

/// <summary>
/// �v���C���[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void PlayerObjectStateThirdAttack::Enter(PlayerObject* _owner, const float _DeltaTime)
{
	// 3�i�K�ڂ̒ʏ�U����Ԃ̃A�j���[�V�����Đ�
	skeletalMeshCompPtr = _owner->GetSkeletalMeshComponentPtr();
	skeletalMeshCompPtr->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateThirdAttack), MPlayRate);
	mIsHit = false;

	// �A�j���[�V�����Đ����Ԏ擾
	mTotalAnimTime = _owner->GetAnimPtr(PlayerState::ePlayerStateThirdAttack)->GetDuration() - 0.6f;
	mElapseTime = 0.0f;
	mHitUntilCount = 0;

	// �q�b�g�X�g�b�v�֌W������
	mIsHitStop = false;
	mHitStopCount = 0;

	// ���W
	mPosition = _owner->GetPosition();
	// �O���x�N�g��
	mForwardVec = _owner->GetForward();
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
	// �I�u�W�F�N�g�̃^�O
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eEnemyAttackDecision)
	{
		mDamageValue = MDamageValueEnemyAttack;
		mIsHit = true;
	}

	_owner->SetDamageValue(mDamageValue);
}