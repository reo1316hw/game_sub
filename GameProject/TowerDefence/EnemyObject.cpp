#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_Pos"> ���W </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
/// <param name="_GpskelName"> gpskel�̃p�X </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
EnemyObject::EnemyObject(const Vector3& _Pos, const Vector3& _Scale, const std::string _GpmeshName, const char* _GpskelName,
	const Tag& _ObjectTag, PlayerObject* _playerPtr)
	: GameObject(_ObjectTag)
	, MPlayRate(1.0f)
	, mNowState(EnemyState::eEnemyStateTrack)
	, mNextState(EnemyState::eEnemyStateTrack)
{
	//GameObject�����o�ϐ��̏�����
	SetScale(_Scale);
	SetPosition(_Pos);

	///���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mSkeltalMeshComponentPtr = new SkeletalMeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mSkeltalMeshComponentPtr->SetMesh(RENDERER->GetMesh(_GpmeshName));
	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Skeleton���Z�b�g(.gpskel)
	mSkeltalMeshComponentPtr->SetSkeleton(RENDERER->GetSkeleton(_GpskelName));

	// �A�j���[�V�����̎擾 & �A�j���[�V�����z��ɃZ�b�g
	mAnimTypes.resize(static_cast<int>(EnemyState::eEnemyStateNum));
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateTrack)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyTrack.gpanim", true);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateWait)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyWait.gpanim", true);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateAttack)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyAttack.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateAttackReady)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyAttackReady.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateLeftMove)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyLeftMove.gpanim", true);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateRightMove)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyRightMove.gpanim", true);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateDamage)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyDamage.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateDeath)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyDeath.gpanim", false);

	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Animation���Z�b�g(.gpanim)
	const Animation* anim = mAnimTypes[static_cast<int>(EnemyState::eEnemyStateTrack)];
	//anim�ϐ��𑬓x1.0f�ōĐ�
	mSkeltalMeshComponentPtr->PlayAnimation(anim, 1.0f);

	mEnemyAttackPtr = new EnemyAttackDecisionObject(this, Tag::eEnemyAttackDecision);

	// �A�N�^�[�X�e�[�g�v�[���̏�����
	mStatePools.push_back(new EnemyObjectStateTrack(_playerPtr));	                                // mStatePool[eEnemyStateTrack]
	mStatePools.push_back(new EnemyObjectStateWait(_playerPtr));	                                // mStatepool[eEnemyStateWait]
	mStatePools.push_back(new EnemyObjectStateAttack(mEnemyAttackPtr));                                              // mStatepool[eEnemyStateAttack]
	mStatePools.push_back(new EnemyObjectStateAttackReady);                                         // mStatepool[eEnemyStateAttackReady]
	mStatePools.push_back(new EnemyObjectStateMove(EnemyState::eEnemyStateLeftMove, _playerPtr));	// mStatepool[eEnemyStateLeftMove]
	mStatePools.push_back(new EnemyObjectStateMove(EnemyState::eEnemyStateRightMove, _playerPtr));	// mStatepool[eEnemyStateRightMove]
	mStatePools.push_back(new EnemyObjectStateDamage);                                              // mStatepool[eEnemyStateDamage];
	mStatePools.push_back(new EnemyObjectStateDeath);                                               // mStatepool[eEnemyStateDeath];

	// ��`�����蔻��
	mBox = AABB(Vector3(-45.0f, -45.0f, 0.0f), Vector3(45.0f, 45.0f, 170.0f));

	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
}

/// <summary>
/// �G�l�~�[���m�̈�������
/// </summary>
/// <param name="_DirTargetEnemyVec"> �ΏۂƂȂ�G�l�~�[�Ɍ������x�N�g�� </param>
void EnemyObject::Separation(const Vector3& _DirTargetEnemyVec)
{
	mStatePools[static_cast<int>(mNowState)]->Separation(this, _DirTargetEnemyVec);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void EnemyObject::UpdateGameObject(float _deltaTime)
{
	// �X�e�[�g�O������X�e�[�g�ύX�����������H
	if (mNowState != mNextState)
	{
		mStatePools[static_cast<int>(mNowState)]->Exit(this, _deltaTime);
		mStatePools[static_cast<int>(mNextState)]->Enter(this, _deltaTime);
		mNowState = mNextState;
		return;
	}

	// �X�e�[�g���s
	mNextState = mStatePools[static_cast<int>(mNowState)]->Update(this, _deltaTime);

	// �X�e�[�g��������X�e�[�g�ύX���������H
	if (mNowState != mNextState)
	{
		mStatePools[static_cast<int>(mNowState)]->Exit(this, _deltaTime);
		mStatePools[static_cast<int>(mNextState)]->Enter(this, _deltaTime);
		mNowState = mNextState;
	}

	mBox = mBoxColliderPtr->GetWorldBox();
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void EnemyObject::OnCollision(const GameObject& _HitObject)
{
	mStatePools[static_cast<int>(mNowState)]->OnCollision(this, _HitObject);

	Tag tag = _HitObject.GetTag();
	
	if (tag == ePlayer)
	{
		//�����߂�����
		float dx1 = _HitObject.GetObjectAABB().m_min.x - mBox.m_max.x;
		float dx2 = _HitObject.GetObjectAABB().m_max.x - mBox.m_min.x;
		float dy1 = _HitObject.GetObjectAABB().m_min.y - mBox.m_max.y;
		float dy2 = _HitObject.GetObjectAABB().m_max.y - mBox.m_min.y;
		float dz1 = _HitObject.GetObjectAABB().m_min.z - mBox.m_max.z;
		float dz2 = _HitObject.GetObjectAABB().m_max.z - mBox.m_min.z;

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

		SetPosition(mPosition);
	}
}