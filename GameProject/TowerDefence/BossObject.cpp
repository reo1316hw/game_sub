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
BossObject::BossObject(const Vector3& _Pos, const Vector3& _Scale, const std::string _GpmeshName, const char* _GpskelName,
	const Tag& _ObjectTag, PlayerObject* _playerPtr)
	: GameObject(_ObjectTag)
	, MMaxHp(500)
	, MPlayRate(1.0f)
	, MHitEffectScale(Vector3(10.0f, -10.0f, 10.0f))
	, MFrontMagicEffectScale(Vector3(15.0f, -15.0f, 15.0f))
	, MAreaMagicEffectScale(Vector3(60.0f, -60.0f, 60.0f))
	, MOverheadEffectScale(Vector3(20.0f, -20.0f, 20.0f))
	, MDangerSignalEffectScale(Vector3(40.0f, -40.0f, 40.0f))
	, MTeleportationEffectScale(Vector3(40.0f, -40.0f, 40.0f))
	, mInitPosition(Vector3::Zero)
	, mNowState(BossState::eBossStateWait)
	, mNextState(BossState::eBossStateTeleportation)
{
	//GameObject�����o�ϐ��̏�����
	SetScale(_Scale);
	SetPosition(_Pos);
	//SetState(State::eDead);
	mInitPosition = mPosition;
	mMaxHp = MMaxHp;
	mHitPoint = mMaxHp;
	// �I�u�W�F�N�g�̃X�P�[���T�C�Y�����߂邽�߂̉E�ӂ̒l��ݒ�
	SetScaleRightSideValue(mHitPoint);

	///���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mSkeltalMeshComponentPtr = new SkeletalMeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mSkeltalMeshComponentPtr->SetMesh(RENDERER->GetMesh(_GpmeshName));
	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Skeleton���Z�b�g(.gpskel)
	mSkeltalMeshComponentPtr->SetSkeleton(RENDERER->GetSkeleton(_GpskelName));

	// �A�j���[�V�����̎擾 & �A�j���[�V�����z��ɃZ�b�g
	mAnimTypes.resize(static_cast<int>(EnemyState::eEnemyStateNum));
	mAnimTypes[static_cast<int>(BossState::eBossStateWait)] = RENDERER->GetAnimation("Assets/Model/Boss/BossWait.gpanim", true);
	mAnimTypes[static_cast<int>(BossState::eBossStateTrack)] = RENDERER->GetAnimation("Assets/Model/Boss/BossTrack.gpanim", true);
	mAnimTypes[static_cast<int>(BossState::eBossStateFrontAttack)] = RENDERER->GetAnimation("Assets/Model/Boss/BossFrontAttack.gpanim", false);
	mAnimTypes[static_cast<int>(BossState::eBossStateAreaAttack)] = RENDERER->GetAnimation("Assets/Model/Boss/BossAreaAttack.gpanim", false);
	mAnimTypes[static_cast<int>(BossState::eBossStateOverheadAttack)] = RENDERER->GetAnimation("Assets/Model/Boss/BossOverheadAttack.gpanim", false);
	mAnimTypes[static_cast<int>(BossState::eBossStateTeleportation)] = RENDERER->GetAnimation("Assets/Model/Boss/BossWait.gpanim", true);
	mAnimTypes[static_cast<int>(BossState::eBossStateImpactDamage)] = RENDERER->GetAnimation("Assets/Model/Boss/BossImpact.gpanim", false);
	mAnimTypes[static_cast<int>(BossState::eBossStateSweepFallDamage)] = RENDERER->GetAnimation("Assets/Model/Boss/BossSweepFall.gpanim", false);
	mAnimTypes[static_cast<int>(BossState::eBossStateFlyingBackDamage)] = RENDERER->GetAnimation("Assets/Model/Boss/BossFlyingBack.gpanim", false);
	mAnimTypes[static_cast<int>(BossState::eBossStateDeath)] = RENDERER->GetAnimation("Assets/Model/Boss/BossDeath.gpanim", false);

	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Animation���Z�b�g(.gpanim)
	const Animation* anim = mAnimTypes[static_cast<int>(BossState::eBossStateTeleportation)];
	//anim�ϐ��𑬓x1.0f�ōĐ�
	mSkeltalMeshComponentPtr->PlayAnimation(anim);

	// �A�N�^�[�X�e�[�g�v�[���̏�����
	mStatePools.push_back(new BossObjectStateWait(_playerPtr));	             // mStatePool[eBossStateWait]
	mStatePools.push_back(new BossObjectStateTrack(_playerPtr));	         // mStatepool[eBossStateTrack]
	mStatePools.push_back(new BossObjectStateFrontAttack(_playerPtr));       // mStatepool[eBossStateFrontAttack]
	mStatePools.push_back(new BossObjectStateAreaAttack(_playerPtr));        // mStatepool[eBossStateAreaAttack]
	mStatePools.push_back(new BossObjectStateOverheadAttack(_playerPtr));    // mStatepool[eBossObjectStateOverheadAttack]
	mStatePools.push_back(new BossObjectStateTeleportation(_playerPtr));     // mStatepool[eBossStateTeleportation]
	mStatePools.push_back(new BossObjectStateImpactDamage(_playerPtr));      // mStatepool[eBossStateImpactDamage]
	mStatePools.push_back(new BossObjectStateSweepFallDamage(_playerPtr));   // mStatepool[eBossStateSweepFallDamage]
	mStatePools.push_back(new BossObjectStateFlyingBackDamage(_playerPtr));  // mStatepool[eBossStateFlyingBackDamage]
	mStatePools.push_back(new BossObjectStateDeath(_playerPtr));             // mStatepool[eBossStateDeath]

	// �q�b�g�G�t�F�N�g����
	new HitEffect(this, MHitEffectScale, Tag::eHItEffect);

	// �O���U���G�t�F�N�g(���j�̕���)�𐶐�
	new FrontCoreMagicEffect(this, MFrontMagicEffectScale, Tag::eFrontCoreMagicEffect);
	// �O���U���G�t�F�N�g(���[�U�[�̕���)�𐶐�
	new FrontLaserMagicEffect(this, MFrontMagicEffectScale, Tag::eFrontLaserMagicEffect);
	// �͈͍U���G�t�F�N�g����
	new AreaMagicEffect(this, MAreaMagicEffectScale, Tag::eAreaMagicEffect);
	// �v���C���[�̓���ɍU������G�t�F�N�g�𐶐�
	new OverheadMagicEffect(this, _playerPtr, MOverheadEffectScale, Tag::eOverheadMagicEffect);
	// �v���C���[����U�����̊댯�M���G�t�F�N�g
	new DangerSignalEffect(this, _playerPtr, MDangerSignalEffectScale, Tag::eDangerSignalEffect);
	// �e���|�[�g�G�t�F�N�g
	new TeleportationEffect(this, MTeleportationEffectScale, Tag::eTeleportationEffect);

	// ��`�����蔻��
	mBox = AABB(Vector3(-45.0f, -45.0f, 0.0f), Vector3(45.0f, 45.0f, 170.0f));

	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
}

/// <summary>
/// �{�X�ƃG�l�~�[�̈�������
/// </summary>
/// <param name="_DirTargetEnemyVec"> �ΏۂƂȂ�G�l�~�[�Ɍ������x�N�g�� </param>
void BossObject::Separation(const Vector3& _DirTargetEnemyVec)
{
	mStatePools[static_cast<int>(mNowState)]->Separation(this, _DirTargetEnemyVec);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void BossObject::UpdateGameObject(float _deltaTime)
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
void BossObject::OnCollision(const GameObject& _HitObject)
{
	// �I�u�W�F�N�g�̃^�O
	Tag tag = _HitObject.GetTag();

	mBox = mBoxColliderPtr->GetWorldBox();

	if (tag == eWall ||
		tag == eGate ||
		tag == eGateDoor ||
		tag == eEnemyGenerator ||
		tag == ePlayer ||
		tag == eBossBootSemitransparentWall)
	{
		//�����߂�����
		float dx1 = _HitObject.GetObjectAABB().m_min.x - mBox.m_max.x;
		float dx2 = _HitObject.GetObjectAABB().m_max.x - mBox.m_min.x;
		float dy1 = _HitObject.GetObjectAABB().m_min.y - mBox.m_max.y;
		float dy2 = _HitObject.GetObjectAABB().m_max.y - mBox.m_min.y;

		float dx = Math::Abs(dx1) < Math::Abs(dx2) ? dx1 : dx2;
		float dy = Math::Abs(dy1) < Math::Abs(dy2) ? dy1 : dy2;

		if (Math::Abs(dx) <= Math::Abs(dy))
		{
			mPosition.x += dx;
		}
		else if (Math::Abs(dy) <= Math::Abs(dx))
		{
			mPosition.y += dy;
		}

		SetPosition(mPosition);
	}

	mStatePools[static_cast<int>(mNowState)]->OnCollision(this, _HitObject);
}