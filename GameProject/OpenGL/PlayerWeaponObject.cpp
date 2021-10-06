#include "pch.h"

PlayerWeaponObject::PlayerWeaponObject(GameObject* _owner, SkeletalMeshComponent* _skMesh, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: GameObject(_ObjectTag, _SceneTag)
	, MSwordRot(Vector3(-Math::PiOver2 * 0.5f, Math::Pi * 0.9f, 0.0f))
	, MSwordPos(Vector3(-70.0f, -5.0f, 135.0f))
	, mWeaponSphere(Vector3::Zero, 0.0f)
	, mWeaponMesh(nullptr)
	, mSphereCollider(nullptr)
{
	// GameObject�����o�ϐ��̏�����
	mTag = _ObjectTag;

	// ����
	mWeaponMesh = new AttackMeshComponent(_owner, _skMesh, "index_01_r");
	mWeaponMesh->SetMesh(RENDERER->GetMesh(_GpmeshName));

	// ����̉~�������Z�b�g
	mWeaponMesh->SetOffsetRotation(MSwordRot);
	// ����̍��W���Z�b�g
	mWeaponMesh->SetOffsetPosition(MSwordPos);

	// ���a
	float radius = 100.0f;
	// ����̋��󓖂��蔻��
	mWeaponSphere = Sphere(mWeaponMesh->GetAttachPosisiton(), radius);
	mSphereCollider = new SphereCollider(this, ColliderTag::Weapon, GetOnCollisionFunc());
	mSphereCollider->SetObjectSphere(mWeaponSphere);
}

void PlayerWeaponObject::UpdateGameObject(float _deltaTime)
{
}

void PlayerWeaponObject::OnCollision(const GameObject& _hitObject)
{
}