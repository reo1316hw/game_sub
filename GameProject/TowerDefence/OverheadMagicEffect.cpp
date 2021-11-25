#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>	
/// <param name="_bossPtr"> �{�X�̃|�C���^ </param>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
OverheadMagicEffect::OverheadMagicEffect(BossObject* _bossPtr, PlayerObject* _playerPtr, const Vector3& _Scale, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MEffectPositionUnUpdateTiming(1.8f)
	, MEffectPlayTiming(2.0f)
	, mElapseTime(0.0f)
	, mBossPtr(_bossPtr)
	, mPlayerPtr(_playerPtr)
	, mEffectComponentPtr(nullptr)
{
	// �G�t�F�N�g�̋�`�����蔻��
	mBox = AABB(Vector3(-25.0f, -25.0f, 0.0f), Vector3(25.0f, 25.0f, 85.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
	// �ŏ��͓����蔻����s��Ȃ��悤�ɂ���
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	// �G�t�F�N�g����
	mEffectComponentPtr = new EffectComponent(this, _Scale, u"Assets/Effect/OverheadMagic.efk", true, true);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void OverheadMagicEffect::UpdateGameObject(float _deltaTime)
{
	// ���݂̃X�e�[�g
	BossState nowState = mBossPtr->GetNowState();

	if (nowState != BossState::eBossStateOverheadAttack)
	{
		mElapseTime = 0.0f;
		return;
	}

	mElapseTime += _deltaTime;

	if (mElapseTime < MEffectPositionUnUpdateTiming)
	{
		mPosition = mPlayerPtr->GetPosition();
		SetPosition(mPosition);
	}

	if (mElapseTime < MEffectPlayTiming)
	{
		return;
	}

	// �Đ��ς݂���Ȃ�������G�t�F�N�g���Đ�����
	if (mEffectComponentPtr->IsPlayedEffect())
	{
		// �G�t�F�N�g���Đ�
		mEffectComponentPtr->PlayEffect();
	}
}