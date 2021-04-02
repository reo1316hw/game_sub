#include <string>

#include "PlayerObject.h"
#include "SkeletalMeshComponent.h"
#include "AttackMeshComponent.h"
#include "Skeleton.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Animation.h"
#include "Renderer.h"
#include "MainCameraObject.h"
#include "InputSystem.h"
#include "BoxCollider.h"

#include "PlayerObjectStateBase.h"
#include "PlayerObjectStateIdle.h"
#include "PlayerObjectStateSwordIdle.h"
#include "PlayerObjectStateSword.h"
#include "PlayerObjectStateRunStart.h"
#include "PlayerObjectStateRunLoop.h"
#include "PlayerObjectStateSprintLoop.h"
#include "PlayerObjectStateRunEnd.h"
//#include "PlayerObjectStateJump.h"
//#include "PlayerObjectStateJumpLoop.h"
//#include "PlayerObjectStateJumpEnd.h"
#include "PlayerObjectStateAttack01.h"
#include "PlayerObjectStateAttack02.h"
#include "PlayerObjectStateAttack03.h"
//#include "PlayerObjectStateHit.h"

PlayerObject::PlayerObject(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const char* _gpskelName, const char* _gpanimName, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_objectTag, _sceneTag)
	, mOffsetPos(Vector3(150.0f,0.0f, 50.0f))
	, mTargetPos(Vector3::Zero)
	, mViewPos(Vector3::Zero)
	, mPlayerBox(Vector3::Zero, Vector3::Zero)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);
	/*gravity = GRAVITY;*/

	//�X�V�̓x�ɍ��Ɉړ�����R���|�[�l���g�𐶐� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	/*new TestComponent(this);*/

	///���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mSkeltalMeshComponent = new SkeletalMeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mSkeltalMeshComponent->SetMesh(RENDERER->GetMesh(_gpmeshName));
	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Skeleton���Z�b�g(.gpskel)
	mSkeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton(_gpskelName));

	// �A�j���[�V�����̎擾 & �A�j���[�V�����z��ɃZ�b�g
	mAnimTypes.resize(static_cast<unsigned int>(PlayerState::PLAYER_STATE_NUM));
	mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_IDLE)] = RENDERER->GetAnimation(_gpanimName, true);
	mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_SWORD_IDLE)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerSwordIdle.gpanim", true);
	mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_DRAWN_SWORD)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerDrawnSword.gpanim", false);
	mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_DRAWN_SWORD_MOVE)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerDrawnSword.gpanim", false);
	mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_SWORD_DELIVERY)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerSwordDelivery.gpanim", false);
	mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_SWORD_DELIVERY_MOVE)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerSwordDelivery.gpanim", false);
	mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_RUN_START)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerIdleToRun.gpanim", false);
	mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_RUN_LOOP)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerSlowRun.gpanim", true);
	mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_SWORD_RUN_LOOP)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerSwordRun.gpanim", true);
	mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_SPRINT_LOOP)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerFastRun.gpanim", true);
	mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_RUN_END)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerRunToIdle.gpanim", false);
	mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_ATTACK1)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAttack01.gpanim", false);
	mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_ATTACK2)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAttack02.gpanim",false);
	mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_ATTACK3)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAttack03.gpanim",false);
	//mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_JUMPSTART)] = RENDERER->GetAnimation("Assets/valkiria_Jumpstart.gpanim");
	//mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_JUMPLOOP)] = RENDERER->GetAnimation("Assets/valkiria_jumploop.gpanim");
	//mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_JUMPEND)] = RENDERER->GetAnimation("Assets/valkiria_jumpend.gpanim");
	//mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_HIT)] = RENDERER->GetAnimation("Assets/valkiria_hit.gpanim");

	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Animation���Z�b�g(.gpanim)
	const Animation* anim = mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_IDLE)];
	//anim�ϐ��𑬓x0.5f�ōĐ�
	mSkeltalMeshComponent->PlayAnimation(anim, 1.0f);

	// ����R���|�[�l���g��t
	// ��
	mMesh = RENDERER->GetMesh("Assets/Model/Player/valkiria_Sword.gpmesh");
	mWeaponMesh = new AttackMeshComponent(this, mSkeltalMeshComponent, "spine_01");
	mWeaponMesh->SetMesh(mMesh);

	// �A�N�^�[�X�e�[�g�v�[���̏�����
	mStatePools.push_back(new PlayerObjectStateIdle(mWeaponMesh,mSkeltalMeshComponent, "spine_01"));					// mStatePool[PLAYER_STATE_IDLE]
	mStatePools.push_back(new PlayerObjectStateSwordIdle);				// mStatePool[PLAYER_STATE_SWORD_IDLE]
	mStatePools.push_back(new PlayerObjectStateSword(mWeaponMesh, mSkeltalMeshComponent, "index_01_r",false,true));		// mStatePool[PLAYER_STATE_DRAWN_SWORD]
	mStatePools.push_back(new PlayerObjectStateSword(mWeaponMesh, mSkeltalMeshComponent, "index_01_r",true,true));		// mStatePool[PLAYER_STATE_DRAWN_SWORD_MOVE]
	mStatePools.push_back(new PlayerObjectStateSword(mWeaponMesh, mSkeltalMeshComponent, "index_01_r",false, false));	// mStatePool[PLAYER_STATE_SWORD_DELIVERY]
	mStatePools.push_back(new PlayerObjectStateSword(mWeaponMesh, mSkeltalMeshComponent, "index_01_r", true, false));		// mStatePool[PLAYER_STATE_SWORD_DELIVERY_MOVE]
	mStatePools.push_back(new PlayerObjectStateRunStart);				// mStatepool[PLAYER_STATE_RUNS_TART]
	mStatePools.push_back(new PlayerObjectStateRunLoop(false));			// mStatepool[PLAYER_STATE_RUN_LOOP]
	mStatePools.push_back(new PlayerObjectStateRunLoop(true));			// mStatepool[PLAYER_STATE_SWORD_RUN_LOOP]
	mStatePools.push_back(new PlayerObjectStateSprintLoop);				// mStatepool[PLAYER_STATE_SPRINT_LOOP]
	mStatePools.push_back(new PlayerObjectStateRunEnd);					// mStatepool[PLAYER_STATE_RUN_END]
	mStatePools.push_back(new PlayerObjectStateAttack01);				// mStatepool[PLAYER_STATE_ATTACK1];
	mStatePools.push_back(new PlayerObjectStateAttack02);				// mStatepool[PLAYER_STATE_ATTACK2];
	mStatePools.push_back(new PlayerObjectStateAttack03);				// mStatepool[PLAYER_STATE_ATTACK3];
	//mStatePools.push_back(new PlayerObjectStateJump);					// mStatepool[PLAYER_STATE_JUMP_START];  
	//mStatePools.push_back(new PlayerObjectStateJumpLoop);				// mStatepool[PLAYER_STATE_JUMP_LOOP];
	//mStatePools.push_back(new PlayerObjectStateJumpEnd);				// mStatepool[PLAYER_STATE_JUMP_END];
	//mStatePools.push_back(new PlayerObjectStateHit);
	
	// �����蔻��
	mMesh = new Mesh;
	mMesh = RENDERER->GetMesh(_gpmeshName);
	mBoxCollider = new BoxCollider(this, ColliderTag::Player, GetOnCollisionFunc());
	mBoxCollider->SetObjectBox(mMesh->GetBox());

	//�v���C���[�̉�]
	SelfRotation(Vector3::UnitZ, 270.0f);
}

PlayerObject::~PlayerObject()
{

}

void PlayerObject::UpdateGameObject(float _deltaTime)
{
	mTargetPos = Vector3(mPosition.x, mPosition.y, mPosition.z + 40.0f);
	mViewPos = mMainCamera->GetPosition();
	mMainCamera->SetViewMatrixLerpObject(mOffsetPos, mTargetPos);

	// �X�e�[�g�O������X�e�[�g�ύX�����������H
	if (mNowState != mNextState)
	{
		mStatePools[static_cast<unsigned int>(mNowState)]->Exit(this, _deltaTime);
		mStatePools[static_cast<unsigned int>(mNextState)]->Enter(this, _deltaTime);
		mNowState = mNextState;
		return;
	}

	// �X�e�[�g���s
	mNextState = mStatePools[static_cast<unsigned int>(mNowState)]->Update(this, _deltaTime);

	// �X�e�[�g��������X�e�[�g�ύX���������H
	if (mNowState != mNextState)
	{
		mStatePools[static_cast<unsigned int>(mNowState)]->Exit(this, _deltaTime);
		mStatePools[static_cast<unsigned int>(mNextState)]->Enter(this, _deltaTime);
		mNowState = mNextState;
	}
}

void PlayerObject::PausingUpdateGameObject()
{

}

void PlayerObject::GameObjectInput(const InputState& _keyState)
{
	mStatePools[static_cast<unsigned int>(mNowState)]->Inipt(this, _keyState);

	//// �U���{�^�������ꂽ�玟�̃X�e�[�g�ֈڍs���鏀��
	//if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_RETURN) == 1)
	//{
	//	// �A�j���[�V�����Đ����Ԏ擾
	//	mTotalAnimTime = mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_ATTACK1)]->GetDuration();
	//	mElapseTime = 0.0f;
	//	attackFlag = true;
	//}

	//// �R���g���[���[�̏\���E�������́A�L�[�{�[�hD�����͂��ꂽ��x�𑫂�
	//if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_A) == 1 ||
	//	_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_SPACE) == 1)
	//{
	//	dirVec += jumpVec;
	//	buttonFlag = true;
	//}
}

void PlayerObject::OnCollision(const GameObject& _hitObject)
{
	//�����߂�����
	mPlayerBox = mBoxCollider->GetWorldBox();

	float dx1 = _hitObject.GetObjectAABB().m_min.x - mPlayerBox.m_max.x;
	float dx2 = _hitObject.GetObjectAABB().m_max.x - mPlayerBox.m_min.x;
	float dy1 = _hitObject.GetObjectAABB().m_min.y - mPlayerBox.m_max.y;
	float dy2 = _hitObject.GetObjectAABB().m_max.y - mPlayerBox.m_min.y;
	float dz1 = _hitObject.GetObjectAABB().m_min.z - mPlayerBox.m_max.z;
	float dz2 = _hitObject.GetObjectAABB().m_max.z - mPlayerBox.m_min.z;

	float dx = Math::Abs(dx1) < Math::Abs(dx2) ? dx1 : dx2;
	float dy = Math::Abs(dy1) < Math::Abs(dy2) ? dy1 : dy2;
	float dz = Math::Abs(dz1) < Math::Abs(dz2) ? dz1 : dz2;

	if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
	{
		mPosition.x += dx;
	}

	if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
	{
		mPosition.y += dy;
	}

	if (Math::Abs(dz) <= Math::Abs(dx) && Math::Abs(dz) <= Math::Abs(dy))
	{
		//charaSpeed = 0.0f;
		mPosition.z += dz;
	}
}

void PlayerObject::SelfRotation(Vector3 _axis, float _angle)
{
	float radian = Math::ToRadians(_angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(_axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}