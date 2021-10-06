#include "pch.h"

EnemyObjectStateDeath::EnemyObjectStateDeath()
{
}

EnemyState EnemyObjectStateDeath::Update(EnemyObject* _owner, const float _DeltaTime)
{
	// �A�j���[�V�������I��������X�V���~�߂�
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		_owner->SetState(Dead);
	}
	return EnemyState::eEnemyStateDeath;
}

void EnemyObjectStateDeath::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateDeath));
}