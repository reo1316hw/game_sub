#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
EnemyObjectStateSweepFallDamage::EnemyObjectStateSweepFallDamage(PlayerObject* _playerPtr)
	: mHitTagList{ Tag::eDashAttackEffect, Tag::eFirstAttackEffect, Tag::eSecondAttackEffect, Tag::eThirdAttackEffect }
	, MDamageValuePlayerFirstAttack(25)
	, MVecShortenVelue(0.1f)
	, MSeparationVecLength(4.0f)
	, MDamageInitSpeed(100.0f)
	, MGravity(4.0f)
	, mIsDamage(false)
	, mHitPoint(0)
	, mDamageValue(0)
	, mHitTagListSize(sizeof(mHitTagList) / sizeof(int))
	, mDamageSpeed(0.0f)
	, mPosition(Vector3::Zero)
	, mNowStateInitPos(Vector3::Zero)
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
EnemyState EnemyObjectStateSweepFallDamage::Update(EnemyObject* _owner, const float _DeltaTime)
{
	if (mHitPoint <= 0)
	{
		return EnemyState::eEnemyStateSweepFallDeath;
	}

 	if (mIsDamage)
	{
		switch (mHitTag)
		{
		case Tag::eDashAttackEffect:

			return EnemyState::eEnemyStateImpactDamage;

		case Tag::eFirstAttackEffect:

			return EnemyState::eEnemyStateImpactDamage;

		case Tag::eThirdAttackEffect:

			return EnemyState::eEnemyStateFlyingBackDamage;
		}
	}

	// ���x
	Vector3 velocity = mDamageSpeed * Vector3::UnitZ;
	mDamageSpeed -= MGravity;

	mPosition += velocity * _DeltaTime;

	if (mPosition.z <= mNowStateInitPos.z)
	{
		mPosition.z = mNowStateInitPos.z;
	}

	_owner->SetPosition(mPosition);

	// �A�j���[�V�������I��������ҋ@��Ԃ�
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		return EnemyState::eEnemyStateStandUp;
	}

	return EnemyState::eEnemyStateSweepFallDamage;
}

/// <summary>
/// �G�l�~�[���m�̈�������
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DirTargetEnemyVec"> �ΏۂƂȂ�G�l�~�[�Ɍ������x�N�g�� </param>
void EnemyObjectStateSweepFallDamage::Separation(EnemyObject* _owner, const Vector3& _DirTargetEnemyVec)
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
void EnemyObjectStateSweepFallDamage::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	mIsDamage = false;

	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateSweepFallDamage));

	// ���W
	mPosition = _owner->GetPosition();
	// ���̃X�e�[�g�ɓ��������̍��W
	mNowStateInitPos = mPosition;
	// �v���C���[�̍��W
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// �v���C���[�Ɍ������x�N�g��
	mDirPlayerVec = playerPos - mPosition;
	mDirPlayerVec.Normalize();

	mDamageSpeed = MDamageInitSpeed;

	// �_���[�W�l
	int damageValue = _owner->GetDamageValue();
	// �̗�
	mHitPoint = _owner->GetHitPoint() - damageValue;

	_owner->RotateToNewForward(mDirPlayerVec);
	_owner->SetHitPoint(mHitPoint);
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void EnemyObjectStateSweepFallDamage::OnCollision(EnemyObject* _owner, const GameObject& _HitObject)
{
	mEnemyPtr = _owner;

	// �I�u�W�F�N�g�̃^�O
	mHitTag = _HitObject.GetTag();

	for (int i = 0; i < mHitTagListSize; i++)
	{
		// �U�����󂯂����̏���
		if (ReceivedAttack(mHitTagList[i], MDamageValuePlayerFirstAttack))
		{
			mPosition.z = mNowStateInitPos.z;
			_owner->SetPosition(mPosition);
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
bool EnemyObjectStateSweepFallDamage::ReceivedAttack(const Tag& _hitTag, const int& _DamageValuePlayerAttack)
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