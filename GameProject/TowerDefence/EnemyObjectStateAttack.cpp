#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyObjectStateAttack::EnemyObjectStateAttack()
	: MAttackSpeed(150.0f)
	, MPlayRate(1.5f)
	, mIsDamage(false)
	, mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
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

	// �A�j���[�V�������I��������ړ���Ԃ�
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		// �����_���l
		int randNum = rand() % 100;
		
		if (randNum < 50)
		{
			return EnemyState::eEnemyStateWait;
		}
		else
		{
			return EnemyState::eEnemyStateMove;
		}
	}
	else if (mIsDamage)
	{
		return EnemyState::eEnemyStateDamage;
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

	mIsDamage = false;
	// �A�j���[�V�����Đ����Ԏ擾
	mTotalAnimTime = _owner->GetAnimPtr(EnemyState::eEnemyStateAttack)->GetDuration() - 0.5f;
	mElapseTime = 0.0f;
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void EnemyObjectStateAttack::OnColision(const GameObject& _HitObject)
{
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eWeapon)
	{
		mIsDamage = true;
	}

	if (tag == Tag::eEnemy)
	{
		_HitObject.GetPosition();
		mIsHitEnemy = true;
	}
}