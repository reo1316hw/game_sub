#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
EnemyObjectStateImpactDamage::EnemyObjectStateImpactDamage(PlayerObject* _playerPtr)
	: mHitTagList{ Tag::eDashAttackEffect, Tag::eFirstAttackEffect, Tag::eSecondAttackEffect, Tag::eThirdAttackEffect }
	, mDamageValueList{ 10, 5, 15, 25 }
	, MDamageSpeed(100.0f)
	, MVecShortenVelue(0.1f)
	, MSeparationVecLength(4.0f)
	, MNotHitTime(0.1f)
	, mIsDamage(false)
	, mHitPoint(0)
	, mDamageValue(0)
	, mHitTagListSize(sizeof(mHitTagList) / sizeof(int))
	, mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
	, mDirPlayerVec(Vector3::Zero)
	, mHitTag(Tag::eOther)
	, mEnemyPtr(nullptr)
	, mPlayerPtr(_playerPtr)
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
/// <returns> �G�l�~�[�̏�� </returns>
EnemyState EnemyObjectStateImpactDamage::Update(EnemyObject* _owner, const float _DeltaTime)
{
	if (mHitPoint <= 0)
	{
		return EnemyState::eEnemyStateFallingBackDeath;
	}

	if (mIsDamage)
	{
		switch (mHitTag)
		{
		case Tag::eFirstAttackEffect:

			Enter(_owner, _DeltaTime);
			break;

		case Tag::eSecondAttackEffect:

			return EnemyState::eEnemyStateSweepFallDamage;
		}
	}

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
		return EnemyState::eEnemyStateWait;
	}

	return EnemyState::eEnemyStateImpactDamage;
}

/// <summary>
/// �G�l�~�[���m�̈�������
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DirTargetEnemyVec"> �ΏۂƂȂ�G�l�~�[�Ɍ������x�N�g�� </param>
void EnemyObjectStateImpactDamage::Separation(EnemyObject* _owner, const Vector3& _DirTargetEnemyVec)
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
/// �G�l�~�[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void EnemyObjectStateImpactDamage::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	mIsDamage = false;

	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateImpactDamage));

	// �A�j���[�V�����Đ����Ԏ擾
	mTotalAnimTime = _owner->GetAnimPtr(EnemyState::eEnemyStateImpactDamage)->GetDuration();
	mElapseTime = 0.0f;

	// ���W
	mPosition = _owner->GetPosition();
	// �v���C���[�̍��W
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// �v���C���[�Ɍ������x�N�g��
	mDirPlayerVec = playerPos - mPosition;
	mDirPlayerVec.Normalize();

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
/// �q�b�g�������̏���
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void EnemyObjectStateImpactDamage::OnCollision(EnemyObject* _owner, const GameObject& _HitObject)
{
	if (mElapseTime <= MNotHitTime)
	{
		return;
	}

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
bool EnemyObjectStateImpactDamage::ReceivedAttack(const Tag& _hitTag, const int& _DamageValuePlayerAttack)
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