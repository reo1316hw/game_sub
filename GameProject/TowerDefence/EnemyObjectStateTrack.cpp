#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
EnemyObjectStateTrack::EnemyObjectStateTrack(PlayerObject* _playerPtr)
	: mHitTagList{ Tag::eDashAttackEffect, Tag::eFirstAttackEffect, Tag::eSecondAttackEffect, Tag::eThirdAttackEffect }
	, MStateTransitionProbability(100)
	, MDamageValuePlayerFirstAttack(25)
	, MTransitionStateDistance(30000.0f)
	, MVecShortenVelue(0.1f)
	, MSeparationVecLength(4.0f)
	, mIsDamage(false)
	, mDamageValue(0)
	, mHitTagListSize(sizeof(mHitTagList) / sizeof(int))
	, mMoveSpeed(2.0f)
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
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
EnemyState EnemyObjectStateTrack::Update(EnemyObject* _owner, const float _DeltaTime)
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

	// �v���C���[�̍��W
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// �v���C���[�Ɍ������x�N�g��
	Vector3 dirPlayerVec = playerPos - mPosition;

	if (mIsDamage)
	{
		return EnemyState::eEnemyStateImpactDamage;
	}

	if (dirPlayerVec.LengthSq() <= MTransitionStateDistance)
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

	dirPlayerVec.Normalize();
	_owner->RotateToNewForward(dirPlayerVec);

	mVelocity = mMoveSpeed * dirPlayerVec;
	mPosition += mVelocity;
	// �L�����̈ʒu�E�X�s�[�h�E�ϊ��s��̍Čv�Z�̕K�v���Z�b�g
	_owner->SetPosition(mPosition);

	return EnemyState::eEnemyStateTrack;
}

/// <summary>
/// �G�l�~�[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void EnemyObjectStateTrack::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateTrack));

	mIsDamage = false;
	// ���W
	mPosition = _owner->GetPosition();
}

/// <summary>
/// �G�l�~�[���m�̈�������
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DirTargetEnemyVec"> �ΏۂƂȂ�G�l�~�[�Ɍ������x�N�g�� </param>
void EnemyObjectStateTrack::Separation(EnemyObject* _owner, const Vector3& _DirTargetEnemyVec)
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
void EnemyObjectStateTrack::OnCollision(EnemyObject* _owner, const GameObject& _HitObject)
{
	mEnemyPtr = _owner;
	// ���W
	mPosition = mEnemyPtr->GetPosition();

	// �I�u�W�F�N�g�̃^�O
	mHitTag = _HitObject.GetTag();

	for (int i = 0; i < mHitTagListSize; i++)
	{
		// �U�����󂯂����̏���
		if (ReceivedAttack(mHitTagList[i], MDamageValuePlayerFirstAttack))
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
bool EnemyObjectStateTrack::ReceivedAttack(const Tag& _hitTag, const int& _DamageValuePlayerAttack)
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