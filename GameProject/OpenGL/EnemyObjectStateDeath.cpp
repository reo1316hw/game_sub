#include "pch.h"

EnemyObjectStateDeath::EnemyObjectStateDeath()
	: mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
{
}

EnemyState EnemyObjectStateDeath::Update(EnemyObject* _owner, const float _DeltaTime)
{
	mElapseTime += _DeltaTime;

	// �A�j���[�V�������I��������X�V���~�߂�
	if (mElapseTime >= 0.3f)
	{
		_owner->SetState(Dead);
	}

	return EnemyState::eEnemyStateDeath;
}

void EnemyObjectStateDeath::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateDeath));

	// �A�j���[�V�����Đ����Ԏ擾
	mTotalAnimTime = _owner->GetAnimPtr(EnemyState::eEnemyStateDeath)->GetDuration();
	mElapseTime = 0.0f;
}