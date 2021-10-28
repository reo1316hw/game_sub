#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyObjectStateAttackReady::EnemyObjectStateAttackReady()
    : MVecShortenVelue(0.1f)
    , MSeparationVecLength(8.0f)
	, mIsDamage(false)
	, mDamageValue(0)
	, MDamageValuePlayerFirstAttack(25)
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
/// <returns> �G�l�~�[�̏�� </returns>
EnemyState EnemyObjectStateAttackReady::Update(EnemyObject* _owner, const float _DeltaTime)
{
	_owner->SetPosition(mPosition);
	
	if (mIsDamage)
	{
		return EnemyState::eEnemyStateDamage;
	}

	// �A�j���[�V�������I��������U����Ԃ֑J��
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		return EnemyState::eEnemyStateAttack;
	}

	return EnemyState::eEnemyStateAttackReady;
}

/// <summary>
/// �G�l�~�[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void EnemyObjectStateAttackReady::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateAttackReady));
	mIsDamage = false;

	// ���W
	mPosition = _owner->GetPosition();
}

/// <summary>
/// �G�l�~�[���m�̈�������
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DirTargetEnemyVec"> �ΏۂƂȂ�G�l�~�[�Ɍ������x�N�g�� </param>
void EnemyObjectStateAttackReady::Separation(EnemyObject* _owner, const Vector3& _DirTargetEnemyVec)
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
void EnemyObjectStateAttackReady::OnCollision(EnemyObject* _owner, const GameObject& _HitObject)
{
	// ���W
	mPosition = _owner->GetPosition();

	// �I�u�W�F�N�g�̃^�O
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eFirstAttackEffect)
	{
		mDamageValue = MDamageValuePlayerFirstAttack;
		mIsDamage = true;
	}

	_owner->SetDamageValue(mDamageValue);
}