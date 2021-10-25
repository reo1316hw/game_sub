#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_skMesh"> �e�N���X�̃X�P���g�����b�V���̃|�C���^ </param>
/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
PlayerWeaponObject::PlayerWeaponObject(SkeletalMeshComponent* _skMesh, const std::string _GpmeshName, const Tag& _ObjectTag, PlayerObject* _playerPtr)
	: GameObject(_ObjectTag)
	, MEnableIsHitTiming(120)
	, MSwordRot(Vector3(-Math::PiOver2 * 0.5f, Math::Pi * 0.9f, 0.0f))
	, MSwordPos(Vector3(-70.0f, -5.0f, 135.0f))
	, mIsHitDisableCount(0)
	, mIsHit(false)
	, mDisableIsHit(false)
	, mWeaponMesh(nullptr)
	, mPlayerPtr(_playerPtr)
{
	// ����̃��b�V��
	mWeaponMesh = new AttackMeshComponent(this, _skMesh ,"index_01_r");
	mWeaponMesh->SetMesh(RENDERER->GetMesh(_GpmeshName));
	mWeaponMesh->SetOffsetRotation(MSwordRot);
	mWeaponMesh->SetOffsetPosition(MSwordPos);

	// ����̋�`�����蔻��
	mBox = AABB(Vector3(-2.0f, -0.0f, -90.0f), Vector3(2.0f, 10.0f, 15.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
	// �ŏ��͓����蔻����s��Ȃ��悤�ɂ���
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void PlayerWeaponObject::UpdateGameObject(float _deltaTime)
{
	// �����U���Ă���Ƃ��̓����蔻��̍X�V����
	if (mBoxColliderPtr)
	{
		Matrix4 mat = mWeaponMesh->GetAttachTransMatrix();
		mBoxColliderPtr->SetForceTransForm(mat);
	}

	// �q�b�g�X�g�b�v���ɃI�u�W�F�N�g�Ə�ɓ������Ă��܂��̂ŁA�q�b�g�t���O����莞�Ԗ����ɂ���
	if (mDisableIsHit)
	{
		mIsHit = false;
		++mIsHitDisableCount;

		if (mIsHitDisableCount >= MEnableIsHitTiming)
		{
			mIsHitDisableCount = 0;
			mDisableIsHit = false;
		}
	}
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void PlayerWeaponObject::OnCollision(const GameObject& _HitObject)
{
	// �I�u�W�F�N�g�̃^�O
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eEnemy && !mDisableIsHit && mPlayerPtr->GetPlayerState() == PlayerState::ePlayerStateThirdAttack)
	{
  		mIsHit = true;
	    mDisableIsHit = true;
	}
}