#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>	
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_dashAttackPtr"> �_�b�V���U����Ԃ̃N���X�̃|�C���^ </param>
DashAttackEffect::DashAttackEffect(PlayerObject* _playerPtr, const Vector3& _Scale, const Tag& _ObjectTag, PlayerObjectStateDashAttack* _dashAttackPtr)
	: GameObject(_ObjectTag)
	, MOffset(10.0f)
	, MHeightCorrection(Vector3(0.0f, 0.0f, 25.0f))
	, mIsHit(false)
	, mDisableIsHit(false)
	, mPlayerPtr(_playerPtr)
	, mEffectComponentPtr(nullptr)
	, mDashAttackPtr(_dashAttackPtr)
{
	SetScale(mPlayerPtr->GetScale());

	// ����̋�`�����蔻��
	mBox = AABB(Vector3(-30.0f, -200.0f, 100.0f), Vector3(150.0f, 200.0f, 100.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
	// �ŏ��͓����蔻����s��Ȃ��悤�ɂ���
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	// �Ռ��G�t�F�N�g����
	mEffectComponentPtr = new EffectComponent(this, _Scale, u"Assets/Effect/DashAttack.efk", true, true);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void DashAttackEffect::UpdateGameObject(float _deltaTime)
{
	// �����␳��̍��W
	Vector3 postionHeightCorrection = mPlayerPtr->GetPosition() + MHeightCorrection;
	// �����␳��̍��W����O�ɂ��炵�����W
	Vector3 offsetPos = mPlayerPtr->GetForward() * MOffset;

	mPosition = postionHeightCorrection + offsetPos;
	SetPosition(mPosition);
	SetRotation(mPlayerPtr->GetRotation());

	// �����蔻��𖳌��ɂ���
	if (!mDashAttackPtr->GetIsCollisionState())
	{
		mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);
		// �q�b�g�X�g�b�v���ł���悤�ɂ���
		mDisableIsHit = false;
		return;
	}

	// �����蔻���L���ɂ���
	if (mDashAttackPtr->GetIsCollisionState())
	{
		// �Đ��ς݂���Ȃ�������G�t�F�N�g���Đ�����
		if (mEffectComponentPtr->IsPlayedEffect())
		{
			// �G�t�F�N�g���Đ�
			mEffectComponentPtr->PlayEffect();
		}

		mBoxColliderPtr->SetCollisionState(CollisionState::eEnableCollision);
	}

	// �q�b�g�X�g�b�v���ɃI�u�W�F�N�g�Ə�ɓ������Ă��܂��̂ŁA�q�b�g�t���O����莞�Ԗ����ɂ���
	if (mDisableIsHit)
	{
		mIsHit = false;
	}
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void DashAttackEffect::OnCollision(const GameObject& _HitObject)
{
	// �I�u�W�F�N�g�̃^�O
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eEnemy && !mDisableIsHit && mPlayerPtr->GetPlayerState() == PlayerState::ePlayerStateDashAttack ||
		tag == Tag::eBoss && !mDisableIsHit && mPlayerPtr->GetPlayerState() == PlayerState::ePlayerStateDashAttack)
	{
		mIsHit = true;
		mDisableIsHit = true;
	}
}