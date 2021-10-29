#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>	
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_secondAttackPtr"> 2�i�K�ڂ̒ʏ�U����Ԃ̃N���X�̃|�C���^ </param>
SecondAttackEffect::SecondAttackEffect(PlayerObject* _playerPtr, const Vector3& _Scale, const Tag& _ObjectTag, PlayerObjectStateSecondAttack* _secondAttackPtr)
	: GameObject(_ObjectTag)
	, MOffset(10.0f)
	, MHeightCorrection(Vector3(0.0f, 0.0f, 25.0f))
	, mPlayerPtr(_playerPtr)
	, mEffectComponentPtr(nullptr)
	, mSecondAttackPtr(_secondAttackPtr)
{
	SetScale(mPlayerPtr->GetScale());

	// ����̋�`�����蔻��
	mBox = AABB(Vector3(-30.0f, -80.0f, 100.0f), Vector3(150.0f, 80.0f, 100.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
	// �ŏ��͓����蔻����s��Ȃ��悤�ɂ���
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	// �G�t�F�N�g����
	mEffectComponentPtr = new EffectComponent(this, _Scale, u"Assets/Effect/SecondAttack.efk", true, true);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void SecondAttackEffect::UpdateGameObject(float _deltaTime)
{
	// �����␳��̍��W
	Vector3 postionHeightCorrection = mPlayerPtr->GetPosition() + MHeightCorrection;
	// �����␳��̍��W����O�ɂ��炵�����W
	Vector3 offsetPos = mPlayerPtr->GetForward() * MOffset;

	mPosition = postionHeightCorrection + offsetPos;
	SetPosition(mPosition);
	SetRotation(mPlayerPtr->GetRotation());

	// �����蔻��𖳌��ɂ���
	if (!mSecondAttackPtr->GetIsCollisionState())
	{
		mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);
		return;
	}

	// �����蔻���L���ɂ���
	if (mSecondAttackPtr->GetIsCollisionState())
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