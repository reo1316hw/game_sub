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
		mMeshComponent = new MeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		mMeshComponent->SetMesh(RENDERER->GetMesh(_gpmeshName));

		// �����蔻��
		mMesh = new Mesh;
		mMesh = RENDERER->GetMesh(_gpmeshName);
		mBoxCollider = new BoxCollider(this, ColliderTag::Wall, GetOnCollisionFunc());
		mBoxCollider->SetObjectBox(mMesh->GetBox());

		break;
	}
}

WallObject::~WallObject()
{
}

void WallObject::UpdateGameObject(float _deltaTime)
{
	mAabb = mBoxCollider->GetWorldBox();
}