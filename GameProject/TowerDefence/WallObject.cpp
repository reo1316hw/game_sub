#include "pch.h"

WallObject::WallObject(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag) :
	GameObject(_objectTag,_sceneTag)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	switch (_sceneTag)
	{
	case SceneBase::Scene::tutorial:

		//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		mMeshComponentPtr = new MeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		mMeshComponentPtr->SetMesh(RENDERER->GetMesh(_gpmeshName));

		// �����蔻��
		mMeshPtr = new Mesh;
		mMeshPtr = RENDERER->GetMesh(_gpmeshName);
		mBoxColliderPtr = new BoxCollider(this, ColliderTag::Wall, GetOnCollisionFunc());
		mBoxColliderPtr->SetObjectBox(mMeshPtr->GetBox());

		break;
	}
}

WallObject::~WallObject()
{
}

void WallObject::UpdateGameObject(float _deltaTime)
{
	mBox = mBoxColliderPtr->GetWorldBox();
}