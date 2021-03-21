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
	, offsetPos(Vector3(150.0f,0.0f, 50.0f))
	, targetPos(Vector3::Zero)
	, viewPos(Vector3::Zero)
	, swordRot(Vector3::Zero)
	, swordPos(Vector3::Zero)
	, playerBox(Vector3::Zero, Vector3::Zero)
{
	//GameObject�����o�ϐ��̏�����
	tag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);
	/*gravity = GRAVITY;*/

	//�X�V�̓x�ɍ��Ɉړ�����R���|�[�l���g�𐶐� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	/*new TestComponent(this);*/

	///���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	skeltalMeshComponent->SetMesh(RENDERER->GetMesh(_gpmeshName));
	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Skeleton���Z�b�g(.gpskel)
	skeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton(_gpskelName));

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
	//mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_JUMPSTART)] = RENDERER->GetAnimation("Assets/valkiria_Jumpstart.gpanim");
	//mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_JUMPLOOP)] = RENDERER->GetAnimation("Assets/valkiria_jumploop.gpanim");
	//mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_JUMPEND)] = RENDERER->GetAnimation("Assets/valkiria_jumpend.gpanim");
	mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_ATTACK1)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAttack01.gpanim", false);
	mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_ATTACK2)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAttack02.gpanim",false);
	mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_ATTACK3)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAttack03.gpanim",false);
	//mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_HIT)] = RENDERER->GetAnimation("Assets/valkiria_hit.gpanim");

	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Animation���Z�b�g(.gpanim)
	const Animation* anim = mAnimTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_IDLE)];
	//anim�ϐ��𑬓x0.5f�ōĐ�
	skeltalMeshComponent->PlayAnimation(anim, 1.0f);

	// �A�N�^�[�X�e�[�g�v�[���̏�����
	mStatePools.push_back(new PlayerObjectStateIdle);					// mStatePool[PLAYER_STATE_IDLE]
	mStatePools.push_back(new PlayerObjectStateSwordIdle);				// mStatePool[PLAYER_STATE_SWORD_IDLE]
	mStatePools.push_back(new PlayerObjectStateSword(false,true));		// mStatePool[PLAYER_STATE_DRAWN_SWORD]
	mStatePools.push_back(new PlayerObjectStateSword(true,true));		// mStatePool[PLAYER_STATE_DRAWN_SWORD_MOVE]
	mStatePools.push_back(new PlayerObjectStateSword(false, false));	// mStatePool[PLAYER_STATE_SWORD_DELIVERY]
	mStatePools.push_back(new PlayerObjectStateSword(true, false));		// mStatePool[PLAYER_STATE_SWORD_DELIVERY_MOVE]
	mStatePools.push_back(new PlayerObjectStateRunStart);				// mStatepool[PLAYER_STATE_RUNS_TART]
	mStatePools.push_back(new PlayerObjectStateRunLoop(false));			// mStatepool[PLAYER_STATE_RUN_LOOP]
	mStatePools.push_back(new PlayerObjectStateRunLoop(true));			// mStatepool[PLAYER_STATE_SWORD_RUN_LOOP]
	mStatePools.push_back(new PlayerObjectStateSprintLoop);				// mStatepool[PLAYER_STATE_SPRINT_LOOP]
	mStatePools.push_back(new PlayerObjectStateRunEnd);					// mStatepool[PLAYER_STATE_RUN_END]
	//mStatePools.push_back(new PlayerObjectStateJump);					// mStatepool[PLAYER_STATE_JUMP_START];  
	//mStatePools.push_back(new PlayerObjectStateJumpLoop);				// mStatepool[PLAYER_STATE_JUMP_LOOP];
	//mStatePools.push_back(new PlayerObjectStateJumpEnd);				// mStatepool[PLAYER_STATE_JUMP_END];
	mStatePools.push_back(new PlayerObjectStateAttack01);				// mStatepool[PLAYER_STATE_ATTACK1];
	mStatePools.push_back(new PlayerObjectStateAttack02);				// mStatepool[PLAYER_STATE_ATTACK2];
	mStatePools.push_back(new PlayerObjectStateAttack03);				// mStatepool[PLAYER_STATE_ATTACK3];
	//mStatePools.push_back(new PlayerObjectStateHit);
	
	// �����蔻��
	mesh = new Mesh;
	mesh = RENDERER->GetMesh(_gpmeshName);
	boxCollider = new BoxCollider(this, ColliderTag::Player, GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());

	//�v���C���[�̉�]
	SelfRotation(Vector3::UnitZ, 270.0f);

	// ����R���|�[�l���g��t
	// ��
	mesh = RENDERER->GetMesh("Assets/Model/Player/valkiria_Sword.gpmesh");
	mWeaponMesh = new AttackMeshComponent(this, skeltalMeshComponent, "index_01_r");
	mWeaponMesh->SetMesh(mesh);
	swordRot = Vector3(-Math::PiOver2 * 0.6f, Math::Pi * 0.4f, 0.0f);
	swordPos = Vector3(0.0f, 0.0f, 110.0f);
	mAttackBoneIndex = mWeaponMesh->GetAttackBoneIndex();
}

PlayerObject::~PlayerObject()
{

}

void PlayerObject::UpdateGameObject(float _deltaTime)
{
	targetPos = Vector3(position.x, position.y, position.z + 40.0f);
	viewPos = mainCamera->GetPosition();
	mainCamera->SetViewMatrixLerpObject(offsetPos, targetPos);

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

	// ����̉~�������Z�b�g
	mWeaponMesh->SetOffsetRotation(swordRot);
	// ����̍��W���Z�b�g
	mWeaponMesh->SetOffsetPosition(swordPos);
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
	playerBox = boxCollider->GetWorldBox();

	float dx1 = _hitObject.aabb.min.x - playerBox.max.x;
	float dx2 = _hitObject.aabb.max.x - playerBox.min.x;
	float dy1 = _hitObject.aabb.min.y - playerBox.max.y;
	float dy2 = _hitObject.aabb.max.y - playerBox.min.y;
	float dz1 = _hitObject.aabb.min.z - playerBox.max.z;
	float dz2 = _hitObject.aabb.max.z - playerBox.min.z;

	float dx = Math::Abs(dx1) < Math::Abs(dx2) ? dx1 : dx2;
	float dy = Math::Abs(dy1) < Math::Abs(dy2) ? dy1 : dy2;
	float dz = Math::Abs(dz1) < Math::Abs(dz2) ? dz1 : dz2;

	if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
	{
		position.x += dx;
	}

	if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
	{
		position.y += dy;
	}

	if (Math::Abs(dz) <= Math::Abs(dx) && Math::Abs(dz) <= Math::Abs(dy))
	{
		//charaSpeed = 0.0f;
		position.z += dz;
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