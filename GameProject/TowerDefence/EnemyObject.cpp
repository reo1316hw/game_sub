#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_Pos"> ���W </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
/// <param name="_GpskelName"> gpskel�̃p�X </param>
/// <param name="_ObjectTag"> �^�O </param>
/// <param name="_SceneTag"> �V�[���^�O </param>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
EnemyObject::EnemyObject(const Vector3& _Pos, const Vector3& _Scale, const std::string _GpmeshName, const char* _GpskelName,
	const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, PlayerObject* _playerPtr)
	: GameObject(_ObjectTag, _SceneTag)
	, MPlayRate(1.0f)
	, mNowState(EnemyState::eEnemyStateTrack)
	, mNextState(EnemyState::eEnemyStateTrack)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _ObjectTag;
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
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateLeftMove)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyMove.gpanim", true);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateRightMove)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyMove.gpanim", true);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateDamage)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyDamage.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateDeath)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyDeath.gpanim", false);

	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Animation���Z�b�g(.gpanim)
	const Animation* anim = mAnimTypes[static_cast<int>(EnemyState::eEnemyStateTrack)];
	//anim�ϐ��𑬓x1.0f�ōĐ�
	mSkeltalMeshComponentPtr->PlayAnimation(anim, 1.0f);

	// �A�N�^�[�X�e�[�g�v�[���̏�����
	mStatePools.push_back(new EnemyObjectStateTrack(_playerPtr));	// mStatePool[eEnemyStateTrack]
	mStatePools.push_back(new EnemyObjectStateWait(_playerPtr));	// mStatepool[eEnemyStateWait]
	mStatePools.push_back(new EnemyObjectStateAttack);              // mStatepool[eEnemyStateAttack]
	mStatePools.push_back(new EnemyObjectStateMove(EnemyState::eEnemyStateLeftMove, _playerPtr));	// mStatepool[eEnemyStateLeftMove]
	mStatePools.push_back(new EnemyObjectStateMove(EnemyState::eEnemyStateRightMove, _playerPtr));	// mStatepool[eEnemyStateRightMove]
	mStatePools.push_back(new EnemyObjectStateDamage);              // mStatepool[eEnemyStateDamage];
	mStatePools.push_back(new EnemyObjectStateDeath);               // mStatepool[eEnemyStateDeath];

	// ��`�����蔻��
	mBox = AABB(Vector3(-15.0f, -15.0f, 0.0f), Vector3(15.0f, 15.0f, 170.0f));

	mBoxColliderPtr = new BoxCollider(this, Tag::eEnemy, GetOnCollisionFunc());
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
	mStatePools[static_cast<int>(mNowState)]->OnColision(this, _HitObject);
}