#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
EnemyObjectStateMove::EnemyObjectStateMove(PlayerObject* _playerPtr)
	: MTransitionTimingNum(120)
	, MTransitionStateDistance(15000.0f)
	, mIsMoving(false)
	, mIsDamage(false)
	, mIsHitEnemy(false)
	, mMoveSpeed(1.0f)
	, mPeriodMoveCount(0)
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
EnemyState EnemyObjectStateMove::Update(EnemyObject* _owner, const float _DeltaTime)
{
	// ���W
	mPosition = _owner->GetPosition();
	// �E���x�N�g��
	Vector3 rightVec = _owner->GetRight();
	rightVec.z = 0.0f;


	// �����_���l
	int randNum = rand() % 100;

	if (!mIsMoving)
	{
		// �t�����̃x�N�g���ɕϊ�
		if (randNum < 50)
		{
			mIsMoving = true;
		}
		else
		{
			mIsMoving = true;
			mMoveSpeed *= -1.0f;
		}
	}
	else
	{
		++mPeriodMoveCount;
	}

	// �v���C���[�̍��W
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// �v���C���[�Ɍ������x�N�g��
	Vector3 dirPlayerVec = playerPos - mPosition;
	dirPlayerVec.Normalize();
	_owner->RotateToNewForward(dirPlayerVec);

	// ���x�x�N�g��
	Vector3 vel = mMoveSpeed * rightVec;
	mPosition += vel;

	if (mPeriodMoveCount >= MTransitionTimingNum)
	{
		mIsMoving = false;

		if (dirPlayerVec.LengthSq() >= MTransitionStateDistance)
		{
			// �����_���l
		    int randNum = rand() % 100;
		    
		    if (randNum < 50)
		    {
		    	return EnemyState::eEnemyStateWait;
		    }
		    else
		    {
		    	return EnemyState::eEnemyStateAttack;
		    }
		}

		return EnemyState::eEnemyStateTrack;
	}
	else
	{
		if (mIsDamage)
		{
			return EnemyState::eEnemyStateDamage;
		}

		if (mIsHitEnemy)
		{
			mPosition = Vector3::Lerp(mPosition)
		}
	}

	_owner->SetPosition(mPosition);

	return EnemyState::eEnemyStateMove;
}

/// <summary>
/// �G�l�~�[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void EnemyObjectStateMove::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateMove));

	mIsDamage = false;
	mIsHitEnemy = false;
	mPeriodMoveCount = 0;
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void EnemyObjectStateMove::OnColision(const GameObject& _HitObject)
{
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eWeapon)
	{
		mIsDamage = true;
	}

	if (tag == Tag::eEnemy)
	{
		Vector3 hitEnemyPos = _HitObject.GetPosition();

		Vector3 dirHitEnemyVec = mPosition - hitEnemyPos;

		dirHitEnemyVec.Normalize();

		Vector3 vec = 50.0f * dirHitEnemyVec;

		mLerpPos += vec;

		mIsHitEnemy = true;
	}
}