#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyObjectStateAttackReady::EnemyObjectStateAttackReady()
    : MVecShortenVelue(0.1f)
    , MSeparationVecLength(8.0f)
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
}

/// <summary>
/// �G�l�~�[���m�̈�������
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DirTargetEnemyVec"> �ΏۂƂȂ�G�l�~�[�Ɍ������x�N�g�� </param>
void EnemyObjectStateAttackReady::Separation(EnemyObject* _owner, const Vector3& _DirTargetEnemyVec)
{
	// ���W
	Vector3 position = _owner->GetPosition();
	// ���������x�N�g��
	Vector3 separationVec = MSeparationVecLength * _DirTargetEnemyVec;

	mVelocity -= separationVec;
	mVelocity *= MVecShortenVelue;
	position += mVelocity;

	_owner->SetPosition(position);
}