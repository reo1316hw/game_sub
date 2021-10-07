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
	// GameObject�����o�ϐ��̏�����
	mTag = _ObjectTag;
	SetScale(mOwner->GetScale());

	// ����
	mWeaponMesh = new AttackMeshComponent(this, _skMesh, "index_01_r");
	mWeaponMesh->SetMesh(RENDERER->GetMesh(_GpmeshName));

	mOffsetRotation = Matrix4::CreateRotationY(MSwordRot.y)
		* Matrix4::CreateRotationX(MSwordRot.x)
		* Matrix4::CreateRotationZ(MSwordRot.z);

	mOffsetPos = Matrix4::CreateTranslation(MSwordPos);

	Matrix4 finalMat, animationMat;
	finalMat = mOffsetRotation * mOffsetPos * animationMat;

	// �A�^�b�`�ʒu�Z�o���X�V
	Vector3 pos = Vector3::Zero;
	mComputeAttachPos = Vector3::Transform(pos, finalMat);
	mComputeTransMatrix = finalMat;

	// ���a
	float radius = 1.0f;
	// ����̋��󓖂��蔻��
	mWeaponSphere = Sphere(mComputeAttachPos + Vector3(70.0f,-60.0f,-60.0f), radius);
	mSphereCollider = new SphereCollider(this, ColliderTag::Weapon, GetOnCollisionFunc());
	mSphereCollider->SetObjectSphere(mWeaponSphere);
}

void PlayerWeaponObject::UpdateGameObject(float _deltaTime)
{
	//Matrix4 finalMat, animationMat;
	//finalMat = mOffsetRotation * mOffsetPos * animationMat;

	//// �A�^�b�`�ʒu�Z�o���X�V
	//Vector3 pos(0, 0, 0);
	//mComputeAttachPos = Vector3::Transform(pos, finalMat);
	//mComputeTransMatrix = finalMat;

	SetPosition(mOwner->GetPosition());
}

void PlayerWeaponObject::OnCollision(const GameObject& _hitObject)
{
}