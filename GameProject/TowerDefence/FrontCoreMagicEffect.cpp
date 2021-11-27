#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>	
/// <param name="_bossPtr"> �{�X�̃|�C���^ </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
FrontCoreMagicEffect::FrontCoreMagicEffect(BossObject* _bossPtr, const Vector3& _Scale, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MBoxEnableTiming(0.5f)
	, MMoveSpeed(10.0f)
	, MHeightCorrection(Vector3(0.0f, 0.0f, 50.0f))
	, mElapseTime(0.0f)
	, mBossPtr(_bossPtr)
	, mEffectComponentPtr(nullptr)
{
	// �G�t�F�N�g�̋�`�����蔻��
	mBox = AABB(Vector3(-20.0f, -20.0f, -20.0f), Vector3(20.0f, 20.0f, 20.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
	// �ŏ��͓����蔻����s��Ȃ��悤�ɂ���
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	// �G�t�F�N�g����
	mEffectComponentPtr = new EffectComponent(this, _Scale, u"Assets/Effect/FrontCoreMagic.efk", true, true);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void FrontCoreMagicEffect::UpdateGameObject(float _deltaTime)
{
	// ���݂̃X�e�[�g
	BossState nowState = mBossPtr->GetNowState();

	if (nowState != BossState::eBossStateFrontAttack)
	{
		mEffectComponentPtr->StopEffect();
		mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);
		mElapseTime = 0.0f;
		return;
	}

	mElapseTime += _deltaTime;

	if (mElapseTime <= MBoxEnableTiming)
	{
		mPosition = mBossPtr->GetPosition() + MHeightCorrection;
		return;
	}

	// �O���x�N�g��
	Vector3 forwardVec = mBossPtr->GetForward();
 	forwardVec.Normalize();
	// ���x
	Vector3 volocity = forwardVec * MMoveSpeed;

	mPosition += volocity;
	SetPosition(mPosition);
	SetRotation(mBossPtr->GetRotation());

	mBoxColliderPtr->SetCollisionState(CollisionState::eEnableCollision);

	// �Đ��ς݂���Ȃ�������G�t�F�N�g���Đ�����
	if (mEffectComponentPtr->IsPlayedEffect())
	{
		// �G�t�F�N�g���Đ�
		mEffectComponentPtr->PlayEffect();
	}
}