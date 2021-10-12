#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
EnemyObjectStateTrack::EnemyObjectStateTrack(PlayerObject* _playerPtr)
	: MTransitionStateDistance(15000.0f)
	, mIsDamage(false)
	, mMoveSpeed(2.0f)
	, mPosition(Vector3::Zero)
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
	// ���W
    mPosition = _owner->GetPosition();
	// �v���C���[�̍��W
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// �v���C���[�Ɍ������x�N�g��
	Vector3 dirPlayerVec = playerPos - mPosition;

	if (dirPlayerVec.LengthSq() <= MTransitionStateDistance)
	{
		// �����_���l
		int randNum = rand() % 90;
		
		if (randNum < 30)
		{
			return EnemyState::eEnemyStateWait;
		}
		else if(randNum >= 30 && randNum < 60)
		{
			return EnemyState::eEnemyStateLeftMove;
		}
		else
		{
			return EnemyState::eEnemyStateRightMove;
		}
	}
	else if (mIsDamage)
	{
		return EnemyState::eEnemyStateDamage;
	}

	dirPlayerVec.Normalize();
	_owner->RotateToNewForward(dirPlayerVec);
	mPosition += mMoveSpeed * dirPlayerVec;
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
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void EnemyObjectStateTrack::OnColision(EnemyObject* _owner, const GameObject& _HitObject)
{
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eWeapon)
	{
		mIsDamage = true;
	}

	//if (tag == Tag::eEnemy)
	//{
	//	//�����߂�����
	//	float dx1 = _HitObject.GetObjectAABB().m_min.x - _owner->GetObjectAABB().m_max.x;
	//	float dx2 = _HitObject.GetObjectAABB().m_max.x - _owner->GetObjectAABB().m_min.x;
	//	float dy1 = _HitObject.GetObjectAABB().m_min.y - _owner->GetObjectAABB().m_max.y;
	//	float dy2 = _HitObject.GetObjectAABB().m_max.y - _owner->GetObjectAABB().m_min.y;
	//	float dz1 = _HitObject.GetObjectAABB().m_min.z - _owner->GetObjectAABB().m_max.z;
	//	float dz2 = _HitObject.GetObjectAABB().m_max.z - _owner->GetObjectAABB().m_min.z;

	//	float dx = Math::Abs(dx1) < Math::Abs(dx2) ? dx1 : dx2;
	//	float dy = Math::Abs(dy1) < Math::Abs(dy2) ? dy1 : dy2;
	//	float dz = Math::Abs(dz1) < Math::Abs(dz2) ? dz1 : dz2;

	//	if (Math::Abs(dx) <= Math::Abs(dy) /*&& Math::Abs(dx) <= Math::Abs(dz)*/)
	//	{
	//		mPosition.x += dx;
	//	}
	//	else if (Math::Abs(dy) <= Math::Abs(dx) /*&& Math::Abs(dy) <= Math::Abs(dz)*/)
	//	{
	//		mPosition.y += dy;
	//	}
	//	//else
	//	////if (Math::Abs(dz) <= Math::Abs(dx) && Math::Abs(dz) <= Math::Abs(dy))
	//	//{
	//	//	mPosition.z += dz;
	//	//}

	//	_owner->SetPosition(mPosition);
	//}
}