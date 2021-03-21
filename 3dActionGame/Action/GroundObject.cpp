#include "GroundObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"

GroundObject::GroundObject(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_objectTag,_sceneTag)
{
	//GameObject�����o�ϐ��̏�����
	tag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	switch (_sceneTag)
	{
	case SceneBase::Scene::tutorial:

		//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
		meshComponent = new MeshComponent(this);
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
		meshComponent->SetMesh(RENDERER->GetMesh(_gpmeshName));

		// �����蔻��
		mesh = new Mesh;
		mesh = RENDERER->GetMesh(_gpmeshName);
		boxCollider = new BoxCollider(this, ColliderTag::Ground, GetOnCollisionFunc());
		boxCollider->SetObjectBox(mesh->GetBox());

		break;
	}
}

GroundObject::~GroundObject()
{
}

void GroundObject::UpdateGameObject(float _deltaTime)
{
	aabb = boxCollider->GetWorldBox();
}

void GroundObject::OnCollision(const GameObject& _hitObject)
{

}