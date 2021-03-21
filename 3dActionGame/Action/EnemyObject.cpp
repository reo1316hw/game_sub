#include <string>

#include "EnemyObject.h"
#include "SkeletalMeshComponent.h"
#include "Skeleton.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Animation.h"
#include "Renderer.h"
#include "MainCameraObject.h"
#include "InputSystem.h"
#include "BoxCollider.h"

EnemyObject::EnemyObject(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const char* _gpskelName, const char* _gpanimName, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_objectTag, _sceneTag)
	, offsetPos(Vector3(0.0f, 50.0f, -150.0f))
{
	//GameObject�����o�ϐ��̏�����
	tag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	moveSpeed = ENENY_SPEED;

	//�X�V�̓x�ɍ��Ɉړ�����R���|�[�l���g�𐶐� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	/*new TestComponent(this);*/

	///���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	skeltalMeshComponent->SetMesh(RENDERER->GetMesh(_gpmeshName));
	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Skeleton���Z�b�g(.gpskel)
	skeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton(_gpskelName));
	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Animation���Z�b�g(.gpanim)
	const Animation* anim = RENDERER->GetAnimation(_gpanimName, true);
	//anim�ϐ��𑬓x0.5f�ōĐ�
	skeltalMeshComponent->PlayAnimation(anim, 1.0f);

	// �����蔻��
	mesh = new Mesh;
	mesh = RENDERER->GetMesh(_gpmeshName);
	boxCollider = new BoxCollider(this, ColliderTag::Enemy, GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());
}

EnemyObject::~EnemyObject()
{

}

void EnemyObject::UpdateGameObject(float _deltaTime)
{

	aabb = boxCollider->GetWorldBox();

	//if (rotationFlag)
	//{
	//	SelfRotation(Vector3::UnitZ, angleZ);
	//	rotationFlag = false;
	//}

	//velocity.y -= gravity;

	//// ��ɍ��W�ɑ��x�𑫂�
	//position += velocity;

	//// ���W���Z�b�g
	//SetPosition(position);
}

void EnemyObject::OnCollision(const GameObject& _hitObject)
{

}

void EnemyObject::SelfRotation(Vector3 _axis, float _angle)
{
	float radian = Math::ToRadians(_angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(_axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}