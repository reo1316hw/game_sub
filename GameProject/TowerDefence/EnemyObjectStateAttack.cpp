#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyObjectStateAttack::EnemyObjectStateAttack()
	: MAttackSpeed(150.0f)
	, MVecShortenVelue(0.1f)
	, MPlayRate(1.5f)
	, MSeparationVecLength(4.0f)
	, mIsDamage(false)
	, mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
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
EnemyState EnemyObjectStateAttack::Update(EnemyObject* _owner, const float _DeltaTime)
{
	// ���W
	mPosition = _owner->GetPosition();
	// �O���x�N�g��
	Vector3 forward = _owner->GetForward();
	// �J�n���x
	float startSpeed = MAttackSpeed * _DeltaTime;
	// �I�����x
	float endSpeed = -MAttackSpeed * _DeltaTime;

	// �U�����ݍ��݈ړ��̂��߂̃A�j���[�V�����Đ����Ԃ̌o�ߊ������v�Z
	mElapseTime += _DeltaTime;
	// �o�ߊ��������ƂɈړ�����
	mPosition += Quintic::EaseIn(mElapseTime, startSpeed, endSpeed, mTotalAnimTime) * forward;

	_owner->SetPosition(mPosition);

	// �A�j���[�V�������I��������ړ���Ԃ�
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
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
/// �G�l�~�[���m�̈�������
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DirTargetEnemyVec"> �ΏۂƂȂ�G�l�~�[�Ɍ������x�N�g�� </param>
void EnemyObjectStateAttack::Separation(EnemyObject* _owner, const Vector3& _DirTargetEnemyVec)
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
void EnemyObjectStateAttack::OnColision(EnemyObject* _owner, const GameObject& _HitObject)
{
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eWeapon)
	{
		mIsDamage = true;
	}

	if (tag == Tag::ePlayer)
	{
		//�����߂�����
		float dx1 = _HitObject.GetObjectAABB().m_min.x - _owner->GetObjectAABB().m_max.x;
		float dx2 = _HitObject.GetObjectAABB().m_max.x - _owner->GetObjectAABB().m_min.x;
		float dy1 = _HitObject.GetObjectAABB().m_min.y - _owner->GetObjectAABB().m_max.y;
		float dy2 = _HitObject.GetObjectAABB().m_max.y - _owner->GetObjectAABB().m_min.y;
		float dz1 = _HitObject.GetObjectAABB().m_min.z - _owner->GetObjectAABB().m_max.z;
		float dz2 = _HitObject.GetObjectAABB().m_max.z - _owner->GetObjectAABB().m_min.z;

		float dx = Math::Abs(dx1) < Math::Abs(dx2) ? dx1 : dx2;
		float dy = Math::Abs(dy1) < Math::Abs(dy2) ? dy1 : dy2;
		float dz = Math::Abs(dz1) < Math::Abs(dz2) ? dz1 : dz2;

		if (Math::Abs(dx) <= Math::Abs(dy) /*&& Math::Abs(dx) <= Math::Abs(dz)*/)
		{
			mPosition.x += dx;
		}
		else if (Math::Abs(dy) <= Math::Abs(dx) /*&& Math::Abs(dy) <= Math::Abs(dz)*/)
		{
			mPosition.y += dy;
		}
		//else
		////if (Math::Abs(dz) <= Math::Abs(dx) && Math::Abs(dz) <= Math::Abs(dy))
		//{
		//	mPosition.z += dz;
		//}

		_owner->SetPosition(mPosition);
	}
}