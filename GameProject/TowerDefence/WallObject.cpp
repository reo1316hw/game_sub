#include "pch.h"

WallObject::WallObject(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag) :
	GameObject(_objectTag)
{
	//GameObject�����o�ϐ��̏�����
	SetScale(_size);
	SetPosition(_pos);

	//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponentPtr = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponentPtr->SetMesh(RENDERER->GetMesh(_gpmeshName));

	// �����蔻��
	mMeshPtr = new Mesh;
	mMeshPtr = RENDERER->GetMesh(_gpmeshName);
	mBoxColliderPtr = new BoxCollider(this, _objectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mMeshPtr->GetBox());
}

WallObject::~WallObject()
{
}

void WallObject::UpdateGameObject(float _deltaTime)
{
	mBox = mBoxColliderPtr->GetWorldBox();
}