#include "pch.h"

EnemyObject::EnemyObject(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const char* _gpskelName, const char* _gpanimName, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_objectTag, _sceneTag)
	, mOffsetPos(Vector3(0.0f, 50.0f, -150.0f))
{
	//GameObject�����o�ϐ��̏�����
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	mMoveSpeed = ENENY_SPEED;

	//�X�V�̓x�ɍ��Ɉړ�����R���|�[�l���g�𐶐� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	/*new TestComponent(this);*/

	///���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mSkeltalMeshComponentPtr = new SkeletalMeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mSkeltalMeshComponentPtr->SetMesh(RENDERER->GetMesh(_gpmeshName));
	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Skeleton���Z�b�g(.gpskel)
	mSkeltalMeshComponentPtr->SetSkeleton(RENDERER->GetSkeleton(_gpskelName));
	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Animation���Z�b�g(.gpanim)
	const Animation* anim = RENDERER->GetAnimation(_gpanimName, true);
	//anim�ϐ��𑬓x0.5f�ōĐ�
	mSkeltalMeshComponentPtr->PlayAnimation(anim, 1.0f);

	// �����蔻��
	mMeshPtr = new Mesh;
	mMeshPtr = RENDERER->GetMesh(_gpmeshName);
	mBoxColliderPtr = new BoxCollider(this, ColliderTag::Enemy, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mMeshPtr->GetBox());
}

EnemyObject::~EnemyObject()
{

}

void EnemyObject::UpdateGameObject(float _deltaTime)
{
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