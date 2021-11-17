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
	, MShouldTutorialUse(false)
	, MMaxHp(50)
	, MPlayRate(1.0f)
	, MHpGaugeScale(Vector3(0.05f, 1.0f, 4.0f))
	, MHitEffectScale(Vector3(10.0f, -10.0f, 10.0f))
	, mInitPosition(Vector3::Zero)
	, mNowState(EnemyState::eEnemyStateWait)
	, mNextState(EnemyState::eEnemyStateTrack)
	, mEnemyHitPointGaugePtr(nullptr)
	, mEnemyHitPointFramePtr(nullptr)
{
	//GameObject�����o�ϐ��̏�����
	SetScale(_Scale);
	SetPosition(_Pos);
	SetState(State::eDead);
	mInitPosition = mPosition;
	mMaxHp = MMaxHp;
	mHitPoint = mMaxHp;

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
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateImpactDamage)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyImpact.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateSweepFallDamage)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemySweepFall.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateFlyingBackDamage)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyFlyingBack.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateStandUp)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyStandUp.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateFallingBackDeath)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyFallingBack.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateSweepFallDeath)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemySweepFall.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateFlyingBackDeath)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyFlyingBack.gpanim", false);

	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Animation���Z�b�g(.gpanim)
	const Animation* anim = mAnimTypes[static_cast<int>(EnemyState::eEnemyStateTrack)];
	//anim�ϐ��𑬓x1.0f�ōĐ�
	mSkeltalMeshComponentPtr->PlayAnimation(anim);

	// �G�l�~�[�̍U�����萶��
	mEnemyAttackPtr = new EnemyAttackDecisionObject(this, Tag::eEnemyAttackDecision);

	// �q�b�g�G�t�F�N�g����
	new HitEffect(this, MHitEffectScale, Tag::eHItEffect);

	// �A�N�^�[�X�e�[�g�v�[���̏�����
	mStatePools.push_back(new EnemyObjectStateTrack(_playerPtr));	                                // mStatePool[eEnemyStateTrack]
	mStatePools.push_back(new EnemyObjectStateWait(_playerPtr));	                                // mStatepool[eEnemyStateWait]
	mStatePools.push_back(new EnemyObjectStateAttack(mEnemyAttackPtr));                             // mStatepool[eEnemyStateAttack]
	mStatePools.push_back(new EnemyObjectStateAttackReady);                                         // mStatepool[eEnemyStateAttackReady]
	mStatePools.push_back(new EnemyObjectStateMove(EnemyState::eEnemyStateLeftMove, _playerPtr));	// mStatepool[eEnemyStateLeftMove]
	mStatePools.push_back(new EnemyObjectStateMove(EnemyState::eEnemyStateRightMove, _playerPtr));	// mStatepool[eEnemyStateRightMove]
	mStatePools.push_back(new EnemyObjectStateImpactDamage(_playerPtr));                            // mStatepool[eEnemyStateImpactDamage];
	mStatePools.push_back(new EnemyObjectStateSweepFallDamage(_playerPtr));                            // mStatepool[eEnemyStateImpactDamage];
	mStatePools.push_back(new EnemyObjectStateFlyingBackDamage(_playerPtr));                            // mStatepool[eEnemyStateImpactDamage];
	mStatePools.push_back(new EnemyObjectStateStandUp(_playerPtr));                            // mStatepool[eEnemyStateImpactDamage];
	mStatePools.push_back(new EnemyObjectStateFallingBackDeath(_playerPtr));                            // mStatepool[eEnemyStateImpactDamage];
	mStatePools.push_back(new EnemyObjectStateSweepFallDeath(_playerPtr));                            // mStatepool[eEnemyStateImpactDamage];
	mStatePools.push_back(new EnemyObjectStateFlyingBackDeath(_playerPtr));                         // mStatepool[eEnemyStateFlyingBackDeath];

	// ��`�����蔻��
	mBox = AABB(Vector3(-45.0f, -45.0f, 0.0f), Vector3(45.0f, 45.0f, 170.0f));

	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);

	// �G�l�~�[��hp�Q�[�W�𐶐�
	mEnemyHitPointGaugePtr = new EnemyHitPointGauge(MHpGaugeScale, "Assets/Texture/EnemyHpGauge.png", Tag::eOther, this);
	// �G�l�~�[��hp�̘g�𐶐�
	mEnemyHitPointFramePtr = new EnemyHitPointFrame(MHpGaugeScale, "Assets/Texture/EnemyHpFrame.png", Tag::eOther, this);
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_ShouldTutorialUse"> �`���[�g���A���Ŏg�p���邩 </param>
/// <param name="_Pos"> ���W </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
/// <param name="_GpskelName"> gpskel�̃p�X </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
EnemyObject::EnemyObject(const bool& _ShouldTutorialUse, const Vector3& _Pos, const Vector3& _Scale, const std::string _GpmeshName, const char* _GpskelName,
	const Tag& _ObjectTag, PlayerObject* _playerPtr)
	: GameObject(_ObjectTag)
	, MShouldTutorialUse(_ShouldTutorialUse)
	, MMaxHp(50)
	, MPlayRate(1.0f)
	, MHpGaugeScale(Vector3(0.05f, 1.0f, 4.0f))
	, MHitEffectScale(Vector3(10.0f, -10.0f, 10.0f))
	, mInitPosition(Vector3::Zero)
	, mNowState(EnemyState::eEnemyStateWait)
	, mNextState(EnemyState::eEnemyStateTrack)
	, mEnemyHitPointGaugePtr(nullptr)
	, mEnemyHitPointFramePtr(nullptr)
{
	//GameObject�����o�ϐ��̏�����
	SetScale(_Scale);
	SetPosition(_Pos);
	mInitPosition = mPosition;
	mMaxHp = MMaxHp;
	mHitPoint = mMaxHp;

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
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateImpactDamage)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyImpact.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateSweepFallDamage)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemySweepFall.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateFlyingBackDamage)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyFlyingBack.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateStandUp)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyStandUp.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateFallingBackDeath)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyFallingBack.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateSweepFallDeath)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemySweepFall.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateFlyingBackDeath)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyFlyingBack.gpanim", false);

	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Animation���Z�b�g(.gpanim)
	const Animation* anim = mAnimTypes[static_cast<int>(EnemyState::eEnemyStateTrack)];
	//anim�ϐ��𑬓x1.0f�ōĐ�
	mSkeltalMeshComponentPtr->PlayAnimation(anim);

	// �G�l�~�[�̍U�����萶��
	mEnemyAttackPtr = new EnemyAttackDecisionObject(this, Tag::eEnemyAttackDecision);

	// �q�b�g�G�t�F�N�g����
	new HitEffect(this, MHitEffectScale, Tag::eHItEffect);

	// �A�N�^�[�X�e�[�g�v�[���̏�����
	mStatePools.push_back(new EnemyObjectStateTrack(_playerPtr));	                                // mStatePool[eEnemyStateTrack]
	mStatePools.push_back(new EnemyObjectStateWait(_playerPtr));	                                // mStatepool[eEnemyStateWait]
	mStatePools.push_back(new EnemyObjectStateAttack(mEnemyAttackPtr));                             // mStatepool[eEnemyStateAttack]
	mStatePools.push_back(new EnemyObjectStateAttackReady);                                         // mStatepool[eEnemyStateAttackReady]
	mStatePools.push_back(new EnemyObjectStateMove(EnemyState::eEnemyStateLeftMove, _playerPtr));	// mStatepool[eEnemyStateLeftMove]
	mStatePools.push_back(new EnemyObjectStateMove(EnemyState::eEnemyStateRightMove, _playerPtr));	// mStatepool[eEnemyStateRightMove]
	mStatePools.push_back(new EnemyObjectStateImpactDamage(_playerPtr));                            // mStatepool[eEnemyStateImpactDamage];
	mStatePools.push_back(new EnemyObjectStateSweepFallDamage(_playerPtr));                            // mStatepool[eEnemyStateImpactDamage];
	mStatePools.push_back(new EnemyObjectStateFlyingBackDamage(_playerPtr));                            // mStatepool[eEnemyStateImpactDamage];
	mStatePools.push_back(new EnemyObjectStateStandUp(_playerPtr));                            // mStatepool[eEnemyStateImpactDamage];
	mStatePools.push_back(new EnemyObjectStateFallingBackDeath(_playerPtr));                            // mStatepool[eEnemyStateImpactDamage];
	mStatePools.push_back(new EnemyObjectStateSweepFallDeath(_playerPtr));                            // mStatepool[eEnemyStateImpactDamage];
	mStatePools.push_back(new EnemyObjectStateFlyingBackDeath(_playerPtr));                         // mStatepool[eEnemyStateFlyingBackDeath];

	// ��`�����蔻��
	mBox = AABB(Vector3(-45.0f, -45.0f, 0.0f), Vector3(45.0f, 45.0f, 170.0f));

	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);

	// �G�l�~�[��hp�Q�[�W�𐶐�
	mEnemyHitPointGaugePtr = new EnemyHitPointGauge(MHpGaugeScale, "Assets/Texture/EnemyHpGauge.png", Tag::eOther, this);
	mEnemyHitPointGaugePtr->SetState(eActive);
	// �G�l�~�[��hp�̘g�𐶐�
	mEnemyHitPointFramePtr = new EnemyHitPointFrame(MHpGaugeScale, "Assets/Texture/EnemyHpFrame.png", Tag::eOther, this);
	mEnemyHitPointFramePtr->SetState(eActive);

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
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void EnemyObject::OnCollision(const GameObject& _HitObject)
{
	// �I�u�W�F�N�g�̃^�O
	Tag tag = _HitObject.GetTag();

	mBox = mBoxColliderPtr->GetWorldBox();

	if (tag == eWall ||
		tag == eGate ||
		tag == eGateDoor ||
		tag == eEnemyGenerator ||
		tag == ePlayer)
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