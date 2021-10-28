#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>	
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_firstAttackPtr"> 1�i�K�ڂ̒ʏ�U����Ԃ̃N���X�̃|�C���^ </param>
FirstAttackEffect::FirstAttackEffect(PlayerObject* _playerPtr, const Tag& _ObjectTag, PlayerObjectStateFirstAttack* _firstAttackPtr)
	: GameObject(_ObjectTag)
	, mPlayerPtr(_playerPtr)
	, mEffectComponentPtr(nullptr)
	, mFirstAttackPtr(_firstAttackPtr)
{
	SetPosition(mPlayerPtr->GetPosition());
	SetScale(mPlayerPtr->GetScale());
	SetRotation(mPlayerPtr->GetRotation());

	// ����̋�`�����蔻��
	mBox = AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc(), false);
	mBoxColliderPtr->SetObjectBox(mBox);
	// �ŏ��͓����蔻����s��Ȃ��悤�ɂ���
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	// �Ռ��G�t�F�N�g����
	mEffectComponentPtr = new EffectComponent(this, u"Assets/Effect/FirstAttack.efk", true, true);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void FirstAttackEffect::UpdateGameObject(float _deltaTime)
{
	SetPosition(mPlayerPtr->GetPosition());
	SetRotation(mPlayerPtr->GetRotation());

	// �����蔻��𖳌��ɂ���
	if (!mFirstAttackPtr->GetIsCollisionState())
	{
		mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);
		return;
	}

	// �����蔻���L���ɂ���
	if (mFirstAttackPtr->GetIsCollisionState())
	{
		// �Đ��ς݂���Ȃ�������G�t�F�N�g���Đ�����
		if (mEffectComponentPtr->IsPlayedEffect())
		{
			// �G�t�F�N�g���Đ�
			mEffectComponentPtr->PlayEffect();
		}
		
		mBoxColliderPtr->SetCollisionState(CollisionState::eEnableCollision);
	}
}