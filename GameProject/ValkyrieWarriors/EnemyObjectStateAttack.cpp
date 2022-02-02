#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_enemyAttackPtr"> �G�l�~�[�̍U������I�u�W�F�N�g�̃|�C���^ </param>
EnemyObjectStateAttack::EnemyObjectStateAttack(EnemyAttackDecisionObject* _enemyAttackPtr)
	: mHitTagList{ Tag::eDashAttackEffect, Tag::eFirstAttackEffect, Tag::eSecondAttackEffect, Tag::eThirdAttackEffect }
	, mDamageValueList{ 10, 5, 15, 25 }
	, MBoxEnableTiming(0.4f)
	, MStateTransitionProbability(100)
	, MAttackSpeed(150.0f)
	, MPlayRate(1.5f)
	, MVecShortenVelue(0.1f)
	, MSeparationVecLength(4.0f)
	, mIsDamage(false)
	, mIsCollisionState(false)
	, mIsOneCollisionState(false)
	, mDamageValue(0)
	, mHitTagListSize(sizeof(mHitTagList) / sizeof(int))
	, mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
	, mBoxDisableTiming(0)
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
	, mForwardVec(Vector3::Zero)
	, mHitTag(Tag::eOther)
	, mEnemyPtr(nullptr)
	, mOwnerBoxCollider(_enemyAttackPtr->GetBoxCollider())
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
/// <returns> �G�l�~�[�̏�� </returns>
EnemyState EnemyObjectStateAttack::Update(EnemyObject* _owner, const float _DeltaTime)
{
	if (mIsDamage)
	{
		switch (mHitTag)
		{
		case Tag::eDashAttackEffect:

			return EnemyState::eEnemyStateImpactDamage;

		case Tag::eFirstAttackEffect:

			return EnemyState::eEnemyStateImpactDamage;

		case Tag::eSecondAttackEffect:

			return EnemyState::eEnemyStateSweepFallDamage;

		case Tag::eThirdAttackEffect:

			return EnemyState::eEnemyStateFlyingBackDamage;
		}
	}

	// �X�V�����O�̍��W
	Vector3 prePosition = mPosition;
	// �J�n���x
	float startSpeed = MAttackSpeed * _DeltaTime;
	// �I�����x
	float endSpeed = -MAttackSpeed * _DeltaTime;

	// �U�����ݍ��݈ړ��̂��߂̃A�j���[�V�����Đ����Ԃ̌o�ߊ������v�Z
	mElapseTime += _DeltaTime;
	// �o�ߊ��������ƂɈړ�����
	mPosition += Quintic::EaseIn(mElapseTime, startSpeed, endSpeed, mTotalAnimTime) * mForwardVec;

	// ���x���v�Z
	mVelocity = prePosition - mPosition;

	_owner->SetPosition(mPosition);

	// �A�j���[�V�������I��������ړ���Ԃ�
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		// �����_���l
		int randNum = rand() % MStateTransitionProbability;
		
		if (randNum < 50)
		{
			return EnemyState::eEnemyStateWait;
		}
		else if(randNum >= 50 && randNum < 80)
		{
			return EnemyState::eEnemyStateLeftMove;
		}
		else
		{
			return EnemyState::eEnemyStateRightMove;
		}
	}

	if (mIsOneCollisionState)
	{
		return EnemyState::eEnemyStateAttack;
	}

	if (mElapseTime >= MBoxEnableTiming)
	{
		// �U���̓����蔻���L���ɂ���
		mIsCollisionState = true;
		mOwnerBoxCollider->SetCollisionState(CollisionState::eEnableCollision);
	}

	if (!mIsCollisionState)
	{
		return EnemyState::eEnemyStateAttack;
	}

	mBoxDisableTiming = MBoxEnableTiming + _DeltaTime;

	if (mElapseTime >= mBoxDisableTiming)
	{
		// �U���̓����蔻��𖳌��ɂ���
		mIsCollisionState = false;
		mIsOneCollisionState = true;
		mOwnerBoxCollider->SetCollisionState(CollisionState::eDisableCollision);
	}

	return EnemyState::eEnemyStateAttack;
}

/// <summary>
/// �G�l�~�[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void EnemyObjectStateAttack::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateAttack), MPlayRate);

	// �A�j���[�V�����Đ����Ԏ擾
	mTotalAnimTime = _owner->GetAnimPtr(EnemyState::eEnemyStateAttack)->GetDuration() - 0.5f;
	mElapseTime = 0.0f;

	mIsDamage = false;
	mIsOneCollisionState = false;

	// ���W
	mPosition = _owner->GetPosition();
	// �O���x�N�g��
	mForwardVec = _owner->GetForward();

	_owner->RotateToNewForward(mForwardVec);
}

/// <summary>
/// �G�l�~�[���m�̈�������
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DirTargetEnemyVec"> �ΏۂƂȂ�G�l�~�[�Ɍ������x�N�g�� </param>
void EnemyObjectStateAttack::Separation(EnemyObject* _owner, const Vector3& _DirTargetEnemyVec)
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
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void EnemyObjectStateAttack::OnCollision(EnemyObject* _owner, const GameObject& _HitObject)
{
	mEnemyPtr = _owner;

	// ���W
	mPosition = mEnemyPtr->GetPosition();

	// �I�u�W�F�N�g�̃^�O
	mHitTag = _HitObject.GetTag();

	for (int i = 0; i < mHitTagListSize; i++)
	{
		// �U�����󂯂����̏���
		if (ReceivedAttack(mHitTagList[i], mDamageValueList[i]))
		{
			return;
		}
	}
}

/// <summary>
/// �U�����󂯂����̏���
/// </summary>
/// <param name="_HitTag"> �q�b�g�����I�u�W�F�N�g�̃^�O </param>
/// <param name="_DamageValuePlayerAttack"> �_���[�W�� </param>
/// <returns> �q�b�g������ </returns>
bool EnemyObjectStateAttack::ReceivedAttack(const Tag& _hitTag, const int& _DamageValuePlayerAttack)
{
	if (mHitTag == _hitTag)
	{
		mDamageValue = _DamageValuePlayerAttack;
		mIsDamage = true;

		mEnemyPtr->SetDamageValue(mDamageValue);
		return true;
	}

	return false;
}