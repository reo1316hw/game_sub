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
	// GameObjectメンバ変数の初期化
	mTag = _ObjectTag;

	// 武器のメッシュ
	mWeaponMesh = new AttackMeshComponent(this, _skMesh ,"index_01_r");
	mWeaponMesh->SetMesh(RENDERER->GetMesh(_GpmeshName));
	mWeaponMesh->SetOffsetRotation(MSwordRot);
	mWeaponMesh->SetOffsetPosition(MSwordPos);

	// 半径
	float radius = 30.0f;
	// 武器の球状当たり判定
	mWeaponSphere = Sphere(Vector3(0.0f, -50.0f, -50.0f), radius);
}

void PlayerWeaponObject::AddAttackHitSphere(const float _Scale)
{
	mSphereCollider = new SphereCollider(this, ColliderTag::Weapon, GetOnCollisionFunc());

	Sphere sphere = mWeaponSphere;
	sphere.m_radius *= _Scale;

	mSphereCollider->SetObjectSphere(sphere);
}

void PlayerWeaponObject::RemoveAttackHitSphere()
{
	if (mSphereCollider)
	{
		delete mSphereCollider;
		mSphereCollider = nullptr;
	}
}

void PlayerWeaponObject::UpdateGameObject(float _deltaTime)
{
	// 武器を振っているときの当たり判定の更新処理
	if (mSphereCollider)
	{
		Matrix4 mat = mWeaponMesh->GetAttachTransMatrix();
		mSphereCollider->SetSphereTransForm(mat);
	}

	// 座標
	Vector3 pos = mOwner->GetPosition();
	SetPosition(pos);
}

void PlayerWeaponObject::OnCollision(const GameObject& _hitObject)
{
}