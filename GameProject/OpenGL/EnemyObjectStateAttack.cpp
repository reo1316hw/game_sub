#include "pch.h"

EnemyObjectStateAttack::EnemyObjectStateAttack(PlayerObject* _playerPtr)
	: MAttackSpeed(300.0f)
	, mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
	, mPlayerPtr(_playerPtr)
{
}

EnemyState EnemyObjectStateAttack::Update(EnemyObject* _owner, const float _DeltaTime)
{
	// �U�����ݍ��݈ړ��̂��߂̃A�j���[�V�����Đ����Ԃ̌o�ߊ������v�Z
	mElapseTime += _DeltaTime;

	// �o�ߊ��������ƂɈړ�����
	Vector3 pos, forward;
	pos = _owner->GetPosition();
	forward = _owner->GetForward();
	float differencePos = -MAttackSpeed * _DeltaTime;
	pos += Quintic::EaseIn(mElapseTime, MAttackSpeed * _DeltaTime, differencePos, mTotalAnimTime) * forward;

	_owner->SetPosition(pos);

	// �A�j���[�V�������I��������ҋ@��Ԃ�
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		return EnemyState::eEnemyStateWait;
	}

	return EnemyState::eEnemyStateAttack;
}

void EnemyObjectStateAttack::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateAttack));

	// �A�j���[�V�����Đ����Ԏ擾
	mTotalAnimTime = _owner->GetAnimPtr(EnemyState::eEnemyStateAttack)->GetDuration();
	mElapseTime = 0.0f;
}