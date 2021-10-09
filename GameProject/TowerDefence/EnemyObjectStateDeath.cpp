#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyObjectStateDeath::EnemyObjectStateDeath()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
/// <returns> �G�l�~�[�̏�� </returns>
EnemyState EnemyObjectStateDeath::Update(EnemyObject* _owner, const float _DeltaTime)
{
	// �A�j���[�V�������I��������X�V���~�߂�
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		_owner->SetState(Dead);
	}
	return EnemyState::eEnemyStateDeath;
}

/// <summary>
/// �G�l�~�[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void EnemyObjectStateDeath::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateDeath));
}