#include "pch.h"

PlayerWeaponObject::PlayerWeaponObject(GameObject* _owner, SkeletalMeshComponent* _skMesh, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: GameObject(_ObjectTag, _SceneTag)
	, MSwordRot(Vector3(-Math::PiOver2 * 0.5f, Math::Pi * 0.9f, 0.0f))
	, MSwordPos(Vector3(-70.0f, -5.0f, 135.0f))
	, mWeaponSphere(Vector3::Zero, 0.0f)
	, mOwner(_owner)
	, mWeaponMesh(nullptr)
	, mSphereCollider(nullptr)
{
	// GameObjectƒƒ“ƒo•Ï”‚Ì‰Šú‰»
	mTag = _ObjectTag;

	// •Ší
	mWeaponMesh = new AttackMeshComponent(this, _skMesh ,"index_01_r");
	mWeaponMesh->SetMesh(RENDERER->GetMesh(_GpmeshName));
	mWeaponMesh->SetOffsetRotation(MSwordRot);
	mWeaponMesh->SetOffsetPosition(MSwordPos);

	// ”¼Œa
	float radius = 1.0f;
	// •Ší‚Ì‹…ó“–‚½‚è”»’è
	mWeaponSphere = Sphere(Vector3(0.0f, -50.0f, 0.0f), radius);
	mSphereCollider = new SphereCollider(this, ColliderTag::Weapon, GetOnCollisionFunc());
	mSphereCollider->SetObjectSphere(mWeaponSphere);
}

void PlayerWeaponObject::UpdateGameObject(float _deltaTime)
{
	// À•W
	Vector3 pos = mOwner->GetPosition();
	SetPosition(pos);
}

void PlayerWeaponObject::OnCollision(const GameObject& _hitObject)
{
}