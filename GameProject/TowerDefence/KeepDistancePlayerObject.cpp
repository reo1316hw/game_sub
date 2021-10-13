#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �e�N���X�̃|�C���^ </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_SceneTag"> �V�[���̃^�O</param>
KeepDistancePlayerObject::KeepDistancePlayerObject(GameObject* _owner, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: GameObject(_ObjectTag, _SceneTag)
	, mSphere(Vector3::Zero, 100.0f)
	, mOwner(_owner)
	//, mSphereColliderPtr(nullptr)
{
	// GameObject�����o�ϐ��̏�����
	mTag = _ObjectTag;
	SetScale(mOwner->GetScale());

	// ��`�����蔻��
	mBox = AABB(Vector3(-150.0f, -150.0f, 0.0f), Vector3(150.0f, 150.0f, 170.0f));

	// ��`�̓����蔻����s���R���|�[�l���g
	mBoxColliderPtr = new BoxCollider(this, Tag::ePlayer, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);

	//// ���̓����蔻����s���R���|�[�l���g
	//mSphereColliderPtr = new SphereCollider(this, _ObjectTag, GetOnCollisionFunc());
	//mSphereColliderPtr->SetObjectSphere(mSphere);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void KeepDistancePlayerObject::UpdateGameObject(float _deltaTime)
{
	mBox = mBoxColliderPtr->GetWorldBox();
	SetPosition(mOwner->GetPosition());
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void KeepDistancePlayerObject::OnCollision(const GameObject& _HitObject)
{
}
