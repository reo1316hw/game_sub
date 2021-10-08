#include "pch.h"

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
	mWeaponBox = AABB(Vector3(-10.0f, -10.0f, 0.0f), Vector3(10.0f, 10.0f, 100.0f));
	//mWeaponBox = AABB(mWeaponMesh->GetMesh()->GetBox());
}

void PlayerWeaponObject::AddAttackHitBox(const float _Scale)
{
	mBoxCollider = new BoxCollider(this, ColliderTag::Weapon, GetOnCollisionFunc());

	AABB box = mWeaponBox;
	box.m_min *= _Scale;
	box.m_max *= _Scale;

	mBoxCollider->SetObjectBox(box);
}

void PlayerWeaponObject::RemoveAttackHitBox()
{
	if (mBoxCollider)
	{
		delete mBoxCollider;
		mBoxCollider = nullptr;
	}
}

void PlayerWeaponObject::UpdateGameObject(float _deltaTime)
{
	// �����U���Ă���Ƃ��̓����蔻��̍X�V����
	if (mBoxCollider)
	{
		Matrix4 mat = mWeaponMesh->GetAttachTransMatrix();
		mBoxCollider->SetForceTransForm(mat);

		// ���W
		Vector3 pos = mat.GetTranslation();
		SetPosition(pos);
	}
}

void PlayerWeaponObject::OnCollision(const GameObject& _hitObject)
{
}