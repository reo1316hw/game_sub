#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_Pos"> ���W </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
/// <param name="_GpskelName"> gpskel�̃p�X </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
PlayerObject::PlayerObject(const Vector3& _Pos, const Vector3& _Scale, const char* _GpmeshName, const char* _GpskelName, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MMaxHp(100)
	, MPlayRate(1.0f)
	, MAngle(270.0f)
	, MAttackEffectScale(Vector3(50.0f, -50.0f, 50.0f))
	, MHitEffectScale(Vector3(25.0f, -25.0f, 25.0f))
	, mNowState(PlayerState::ePlayerStateIdle)
	, mNextState(PlayerState::ePlayerStateIdle)
	, mSkeltalMeshComponentPtr(nullptr)
	, mMainCameraPtr(nullptr)
	, mRunLoopPtr(nullptr)
	, mSprintStartPtr(nullptr)
	, mSprintLoopPtr(nullptr)
	, mFirstAttackPtr(nullptr)
	, mSecondAttackPtr(nullptr)
	, mThirdAttackPtr(nullptr)
{
	// GameObject�����o�ϐ��̏�����
	SetScale(_Scale);
	SetPosition(_Pos);
	mMaxHp = MMaxHp;
	mHitPoint = mMaxHp;

	// ���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mSkeltalMeshComponentPtr = new SkeletalMeshComponent(this);
	// Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mSkeltalMeshComponentPtr->SetMesh(RENDERER->GetMesh(_GpmeshName));
	// Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Skeleton���Z�b�g(.gpskel)
	mSkeltalMeshComponentPtr->SetSkeleton(RENDERER->GetSkeleton(_GpskelName));

	// �A�j���[�V�����̎擾 & �A�j���[�V�����z��ɃZ�b�g
	mAnimTypes.resize(static_cast<int>(PlayerState::ePlayerStateNum));
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateIdle)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerIdle.gpanim", true);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateRunLoop)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerRun.gpanim", true);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateSprintStart)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerSprintStart.gpanim", false);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateSprintLoop)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerSprint.gpanim", true);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateFirstAttack)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerFirstAttack.gpanim", false);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateSecondAttack)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerSecondAttack.gpanim", false);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateThirdAttack)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerThirdAttack.gpanim", false);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateDashAttack)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerDashAttack.gpanim", false);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateDamage)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerDamage.gpanim", false);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateDeath)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerDeath.gpanim", false);

	// Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Animation���Z�b�g(.gpanim)
	const Animation* anim = mAnimTypes[static_cast<int>(PlayerState::ePlayerStateIdle)];
	// anim�ϐ��𑬓x1.0f�ōĐ�
	mSkeltalMeshComponentPtr->PlayAnimation(anim, MPlayRate);

	// ���S��Ԃ̃N���X�̃|�C���^
	PlayerObjectStateDeath* deathPtr = nullptr;
	// �_�b�V���U����Ԃ̃N���X�̃|�C���^
	PlayerObjectStateDashAttack* dashAttackPtr = nullptr;

	// �A�N�^�[�X�e�[�g�v�[���̏�����
	mStatePools.push_back(new PlayerObjectStateIdle());	                  // mStatePool[ePlayerStateIdle]
	mStatePools.push_back(mRunLoopPtr = new PlayerObjectStateRunLoop);	              // mStatepool[ePlayerStateRunLoop]
	mStatePools.push_back(mSprintStartPtr = new PlayerObjectStateSprintStart);              // mStatepool[ePlayerStateSprintStart]
	mStatePools.push_back(mSprintLoopPtr = new PlayerObjectStateSprintLoop);	              // mStatepool[ePlayerStateSprintLoop]
	mStatePools.push_back(mFirstAttackPtr = new PlayerObjectStateFirstAttack);  // mStatepool[ePlayerStateFirstAttack];
	mStatePools.push_back(mSecondAttackPtr = new PlayerObjectStateSecondAttack); // mStatepool[ePlayerStateSecondAttack];
	mStatePools.push_back(mThirdAttackPtr = new PlayerObjectStateThirdAttack);  // mStatepool[ePlayerStateThirdAttack];
	mStatePools.push_back(dashAttackPtr = new PlayerObjectStateDashAttack);   // mStatepool[ePlayerStateDashAttack];
	mStatePools.push_back(new PlayerObjectStateDamage);	                  // mStatepool[ePlayerStateDamage]
	mStatePools.push_back(deathPtr = new PlayerObjectStateDeath);	      // mStatepool[ePlayerStateDeath]

	// ����
	new PlayerWeaponObject(mSkeltalMeshComponentPtr, "Assets/Model/Sword/Sword.gpmesh", Tag::eWeapon, deathPtr);

	// 1�i�K�ڂ̒ʏ�U���G�t�F�N�g�𐶐�
	FirstAttackEffect* firstAttackEffectPtr = new FirstAttackEffect(this, MAttackEffectScale, Tag::eFirstAttackEffect, mFirstAttackPtr);
	// 2�i�K�ڂ̒ʏ�U���G�t�F�N�g�𐶐�
	SecondAttackEffect* secondAttackEffectPtr = new SecondAttackEffect(this, MAttackEffectScale, Tag::eSecondAttackEffect, mSecondAttackPtr);
	// 3�i�K�ڂ̒ʏ�U���G�t�F�N�g�𐶐�
	ThirdAttackEffect* thirdAttackEffectPtr = new ThirdAttackEffect(this, MAttackEffectScale, Tag::eThirdAttackEffect, mThirdAttackPtr);
	// �_�b�V���U���G�t�F�N�g�𐶐�
	DashAttackEffect* dashEffectPtr = new DashAttackEffect(this, MAttackEffectScale, Tag::eDashAttackEffect, dashAttackPtr);

	// 1�i�K�ڂ̒ʏ�U����ԃN���X��1�i�K�ڂ̒ʏ�U���G�t�F�N�g�N���X�̃|�C���^��n��
	mFirstAttackPtr->SetFirstAttackEffectPtr(firstAttackEffectPtr);
	// 2�i�K�ڂ̒ʏ�U����ԃN���X��2�i�K�ڂ̒ʏ�U���G�t�F�N�g�N���X�̃|�C���^��n��
	mSecondAttackPtr->SetSecondAttackEffectPtr(secondAttackEffectPtr);
	// 3�i�K�ڂ̒ʏ�U����ԃN���X��3�i�K�ڂ̒ʏ�U���G�t�F�N�g�N���X�̃|�C���^��n��
	mThirdAttackPtr->SetThirdAttackEffectPtr(thirdAttackEffectPtr);
	// �_�b�V���U����ԃN���X�Ƀ_�b�V���U���G�t�F�N�g�N���X�̃|�C���^��n��
	dashAttackPtr->SetDashAttackEffectPtr(dashEffectPtr);

	// �q�b�g�G�t�F�N�g����
	new HitEffect(this, MHitEffectScale, Tag::eHItEffect);

	// ��`�����蔻��
	mBox = AABB(Vector3(-30.0f, -30.0f, 0.0f), Vector3(30.0f, 30.0f, 170.0f));

	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
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
	//// �I�u�W�F�N�g�̃^�O
	//Tag tag = _HitObject.GetTag();

	//if (tag == eWall)
	//{
	//	//�����߂�����
	//	float dx1 = _HitObject.GetObjectAABB().m_min.x - mBox.m_max.x;
	//	float dx2 = _HitObject.GetObjectAABB().m_max.x - mBox.m_min.x;
	//	float dy1 = _HitObject.GetObjectAABB().m_min.y - mBox.m_max.y;
	//	float dy2 = _HitObject.GetObjectAABB().m_max.y - mBox.m_min.y;
	//	float dz1 = _HitObject.GetObjectAABB().m_min.z - mBox.m_max.z;
	//	float dz2 = _HitObject.GetObjectAABB().m_max.z - mBox.m_min.z;

	//	float dx = Math::Abs(dx1) < Math::Abs(dx2) ? dx1 : dx2;
	//	float dy = Math::Abs(dy1) < Math::Abs(dy2) ? dy1 : dy2;
	//	float dz = Math::Abs(dz1) < Math::Abs(dz2) ? dz1 : dz2;

	//	if (Math::Abs(dx) <= Math::Abs(dy))
	//	{
	//		mPosition.x += dx;
	//	}
	//	else if (Math::Abs(dy) <= Math::Abs(dx))
	//	{
	//		mPosition.y += dy;
	//	}

	//	SetPosition(mPosition);
	//}

	mStatePools[static_cast<int>(mNowState)]->OnCollision(this, _HitObject);
}

/// <summary>
/// �J�����̃|�C���^��ݒ�
/// </summary>
/// <param name="_mainCameraPtr"> �J�����̃|�C���^ </param>
void PlayerObject::SetMainCameraPtr(MainCameraObject* _mainCameraPtr)
{
	mRunLoopPtr->SetMainCameraPtr(_mainCameraPtr);
	mSprintStartPtr->SetMainCameraPtr(_mainCameraPtr);
	mSprintLoopPtr->SetMainCameraPtr(_mainCameraPtr);
	mFirstAttackPtr->SetMainCameraPtr(_mainCameraPtr);
	mSecondAttackPtr->SetMainCameraPtr(_mainCameraPtr);
	mThirdAttackPtr->SetMainCameraPtr(_mainCameraPtr);
}