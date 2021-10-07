#include "pch.h"

PlayerWeaponObject::PlayerWeaponObject(GameObject* _owner, SkeletalMeshComponent* _skMesh, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: GameObject(_ObjectTag, _SceneTag)
	, mAttackBoneIndex(0)
	, MSwordRot(Vector3(-Math::PiOver2 * 0.5f, Math::Pi * 0.9f, 0.0f))
	//, MSwordRot(Vector3(Math::Pi, -0.5f, 0.0f))
	, MSwordPos(Vector3(-70.0f, -5.0f, 135.0f))
	, mWeaponSphere(Vector3::Zero, 0.0f)
	, mOwner(_owner)
	, mWeaponMesh(nullptr)
	, mSphereCollider(nullptr)
	, mAttackSkeletalMesh(_skMesh)
{
	// GameObjectoΟΜϊ»
	mTag = _ObjectTag;
	SetScale(mOwner->GetScale());

	// ν
	mWeaponMesh = new MeshComponent(this);
	mWeaponMesh->SetMesh(RENDERER->GetMesh(_GpmeshName));

	mOffsetRotation = Matrix4::CreateRotationY(MSwordRot.y)
		* Matrix4::CreateRotationX(MSwordRot.x)
		* Matrix4::CreateRotationZ(MSwordRot.z);

	mOffsetPos = Matrix4::CreateTranslation(MSwordPos);

	mAttackBoneIndex = _skMesh->GetBoneIndexFromName("index_01_r");

	// Όa
	float radius = 1.0f;
	// νΜσ½θ»θ
	mWeaponSphere = Sphere(Vector3(0.0f, -50.0f, 0.0f), radius);
	mSphereCollider = new SphereCollider(this, ColliderTag::Weapon, GetOnCollisionFunc());
	mSphereCollider->SetObjectSphere(mWeaponSphere);
}

void PlayerWeaponObject::UpdateGameObject(float _deltaTime)
{
	Matrix4 finalMat, animationMat;
	mAttackSkeletalMesh->GetMatrixFromBoneIndex(animationMat, mAttackBoneIndex);
	finalMat = mOffsetRotation * mOffsetPos * animationMat;

	// A^b`ΚuZoXV
	Vector3 pos = Vector3::Zero;
	mComputeAttachPos = Vector3::Transform(pos, mOffsetPos * animationMat);

	Quaternion q = Quaternion::Concatenate(Quaternion::MatrixToQuaternion(mOffsetRotation), mOwner->GetRotation());
	SetRotation(q);
	//SetRotation(Quaternion::MatrixToQuaternion(mOffsetRotation));
	SetPosition(mComputeAttachPos);

	//mWorldTransform = finalMat;
}

void PlayerWeaponObject::OnCollision(const GameObject& _hitObject)
{
}