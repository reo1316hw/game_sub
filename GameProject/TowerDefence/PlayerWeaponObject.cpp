#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �e�N���X�̃|�C���^ </param>
/// <param name="_skMesh"> �e�N���X�̃X�P���g�����b�V���̃|�C���^ </param>
/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_SceneTag"> �V�[���̃^�O</param>
PlayerWeaponObject::PlayerWeaponObject(GameObject* _owner, SkeletalMeshComponent* _skMesh, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: GameObject(_ObjectTag, _SceneTag)
	, MSwordRot(Vector3(-Math::PiOver2 * 0.5f, Math::Pi * 0.9f, 0.0f))
	, MSwordPos(Vector3(-70.0f, -5.0f, 135.0f))
	, mWeaponBox(Vector3::Zero, Vector3::Zero)
	, mOwner(_owner)
	, mWeaponMesh(nullptr)
	, mBoxCollider(nullptr)
{
	// GameObject�����o�ϐ��̏�����
	mTag = _ObjectTag;

	// ����̃��b�V��
	mWeaponMesh = new AttackMeshComponent(this, _skMesh ,"index_01_r");
	mWeaponMesh->SetMesh(RENDERER->GetMesh(_GpmeshName));
	mWeaponMesh->SetOffsetRotation(MSwordRot);
	mWeaponMesh->SetOffsetPosition(MSwordPos);

	// ����̋�`�����蔻��
	mWeaponBox = AABB(Vector3(-2.0f, -0.0f, -90.0f), Vector3(2.0f, 10.0f, 15.0f));
}

/// <summary>
/// �U���p�̓����蔻���ǉ�
/// </summary>
/// <param name="_Scale"> �����蔻��̑傫�� </param>
void PlayerWeaponObject::AddAttackHitBox(const float _Scale)
{
	mBoxCollider = new BoxCollider(this, ColliderTag::Weapon, GetOnCollisionFunc());

	AABB box = mWeaponBox;
	box.m_min *= _Scale;
	box.m_max *= _Scale;

	mBoxCollider->SetObjectBox(box);
}

/// <summary>
/// �U���p�̓����蔻����폜
/// </summary>
void PlayerWeaponObject::RemoveAttackHitBox()
{
	if (mBoxCollider)
	{
		delete mBoxCollider;
		mBoxCollider = nullptr;
	}
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void PlayerWeaponObject::UpdateGameObject(float _deltaTime)
{
	// �����U���Ă���Ƃ��̓����蔻��̍X�V����
	if (mBoxCollider)
	{
		Matrix4 mat = mWeaponMesh->GetAttachTransMatrix();
		mBoxCollider->SetForceTransForm(mat);
	}
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void PlayerWeaponObject::OnCollision(const GameObject& _HitObject)
{
}