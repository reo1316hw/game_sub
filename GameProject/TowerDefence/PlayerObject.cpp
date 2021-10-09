
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
PlayerObject::PlayerObject(const Vector3& _Pos, const Vector3& _Scale, const char* _GpmeshName, const char* _GpskelName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: GameObject(_ObjectTag, _SceneTag)
	, MCameraOffset(Vector3(-150.0f, -150.0f, -150.0f))
	, MTargetOffset(Vector3(0.0f, 0.0f, 40.0f))
	, MPlayRate(1.0f)
	, MAngle(270.0f)
	, mTargetPos(Vector3::Zero)
	, mCameraPos(Vector3::Zero)
	, mNowState(PlayerState::ePlayerStateIdle)
	, mNextState(PlayerState::ePlayerStateIdle)
	, mSkeltalMeshComponentPtr(nullptr)
	, mWeaponPtr(nullptr)
{
	// GameObject�����o�ϐ��̏�����
	mTag = _ObjectTag;
	SetScale(_Scale);
	SetPosition(_Pos);

	// ���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mSkeltalMeshComponentPtr = new SkeletalMeshComponent(this);
	// Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mSkeltalMeshComponentPtr->SetMesh(RENDERER->GetMesh(_GpmeshName));
	// Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Skeleton���Z�b�g(.gpskel)
	mSkeltalMeshComponentPtr->SetSkeleton(RENDERER->GetSkeleton(_GpskelName));

	// �A�j���[�V�����̎擾 & �A�j���[�V�����z��ɃZ�b�g
	mAnimTypes.resize(static_cast<int>(PlayerState::ePlayerStateNum));
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateIdle)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerSwordIdle.gpanim", true);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateRunLoop)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerSwordRun.gpanim", true);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateSprintStart)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerIdleToRun.gpanim", false);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateSprintLoop)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerFastRun.gpanim", true);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateFirstAttack)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAttack01.gpanim", false);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateSecondAttack)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAttack02.gpanim", false);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateThirdAttack)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAttack03.gpanim", false);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateDashAttack)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerDashAttack.gpanim", false);

	// Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Animation���Z�b�g(.gpanim)
	const Animation* anim = mAnimTypes[static_cast<int>(PlayerState::ePlayerStateIdle)];
	// anim�ϐ��𑬓x1.0f�ōĐ�
	mSkeltalMeshComponentPtr->PlayAnimation(anim, MPlayRate);

	// ����
	mWeaponPtr = new PlayerWeaponObject(this, mSkeltalMeshComponentPtr, "Assets/Model/Sword/Sword.gpmesh", Tag::Weapon, _SceneTag);

	// �A�N�^�[�X�e�[�g�v�[���̏�����
	mStatePools.push_back(new PlayerObjectStateIdle());	      // mStatePool[ePlayerStateIdle]
	mStatePools.push_back(new PlayerObjectStateRunLoop);	  // mStatepool[ePlayerStateRunLoop]
	mStatePools.push_back(new PlayerObjectStateSprintStart);  // mStatepool[ePlayerStateSprintStart]
	mStatePools.push_back(new PlayerObjectStateSprintLoop);	  // mStatepool[ePlayerStateSprintLoop]
	mStatePools.push_back(new PlayerObjectStateFirstAttack(mWeaponPtr));  // mStatepool[ePlayerStateFirstAttack];
	mStatePools.push_back(new PlayerObjectStateSecondAttack(mWeaponPtr)); // mStatepool[ePlayerStateSecondAttack];
	mStatePools.push_back(new PlayerObjectStateThirdAttack(mWeaponPtr));  // mStatepool[ePlayerStateThirdAttack];
	mStatePools.push_back(new PlayerObjectStateDashAttack(mWeaponPtr));   // mStatepool[ePlayerStateDashAttack];

	// ��`�����蔻��
	mBox = AABB(Vector3(-30.0f, -30.0f, 0.0f), Vector3(30.0f, 30.0f, 170.0f));

	mBoxColliderPtr = new BoxCollider(this, ColliderTag::Player, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);

	// ��]����
	SelfRotation(Vector3::UnitZ, MAngle);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void PlayerObject::UpdateGameObject(float _deltaTime)
{
	mTargetPos = mPosition + MTargetOffset;
	mCameraPos = mMainCamera->GetPosition();
	// ���������W�̐ݒ�
	mMainCamera->SetViewObject(MCameraOffset, mTargetPos);

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
/// ���͂������Ŏ󂯎��X�V�֐�
/// ��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
/// </summary>
/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
void PlayerObject::GameObjectInput(const InputState& _KeyState)
{
	mStatePools[static_cast<int>(mNowState)]->Input(this, _KeyState);
}

/// <summary>
/// ��]����
/// </summary>
/// <param name="_Axis"> �� </param>
/// <param name="_Angle"> �p�x </param>
void PlayerObject::SelfRotation(Vector3 _axis, float _angle)
{
	float radian = Math::ToRadians(_angle);
	Quaternion rot = mRotation;
	Quaternion inc(_axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void PlayerObject::OnCollision(const GameObject& _HitObject)
{
	////�����߂�����
	//float dx1 = _HitObject.GetObjectAABB().m_min.x - mBox.m_max.x;
	//float dx2 = _HitObject.GetObjectAABB().m_max.x - mBox.m_min.x;
	//float dy1 = _HitObject.GetObjectAABB().m_min.y - mBox.m_max.y;
	//float dy2 = _HitObject.GetObjectAABB().m_max.y - mBox.m_min.y;
	//float dz1 = _HitObject.GetObjectAABB().m_min.z - mBox.m_max.z;
	//float dz2 = _HitObject.GetObjectAABB().m_max.z - mBox.m_min.z;

	//float dx = Math::Abs(dx1) < Math::Abs(dx2) ? dx1 : dx2;
	//float dy = Math::Abs(dy1) < Math::Abs(dy2) ? dy1 : dy2;
	//float dz = Math::Abs(dz1) < Math::Abs(dz2) ? dz1 : dz2;

	//if (Math::Abs(dx) <= Math::Abs(dy)/* && Math::Abs(dx) <= Math::Abs(dz)*/)
	//{
	//	mPosition.x += dx;
	//}
	//else if (Math::Abs(dy) <= Math::Abs(dx) /*&& Math::Abs(dy) <= Math::Abs(dz)*/)
	//{
	//	mPosition.y += dy;
	//}
	////else
	////	//if (Math::Abs(dz) <= Math::Abs(dx) && Math::Abs(dz) <= Math::Abs(dy))
	////{
	////	mPosition.z += dz;
	////}

	//SetPosition(mPosition);
}