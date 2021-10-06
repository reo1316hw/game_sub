#include "pch.h"

PlayerWeaponObject::PlayerWeaponObject(GameObject* _owner, SkeletalMeshComponent* _skMesh, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: GameObject(_ObjectTag, _SceneTag)
	, MSwordRot(Vector3(-Math::PiOver2 * 0.5f, Math::Pi * 0.9f, 0.0f))
	, MSwordPos(Vector3(-70.0f, -5.0f, 135.0f))
	, mWeaponSphere(Vector3::Zero, 0.0f)
	, mWeaponMesh(nullptr)
	, mSphereCollider(nullptr)
{
	// GameObjectメンバ変数の初期化
	mTag = _ObjectTag;

	// 武器
	mWeaponMesh = new AttackMeshComponent(_owner, _skMesh, "index_01_r");
	mWeaponMesh->SetMesh(RENDERER->GetMesh(_GpmeshName));

	// 武器の円周率をセット
	mWeaponMesh->SetOffsetRotation(MSwordRot);
	// 武器の座標をセット
	mWeaponMesh->SetOffsetPosition(MSwordPos);

	// 半径
	float radius = 100.0f;
	// 武器の球状当たり判定
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