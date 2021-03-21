#pragma once
#include "MeshComponent.h"
#include "Math.h"
#include <cstddef>

// スケルタルメッシュの関節に取り付け可能なメッシュ
class AttackMeshComponent : public MeshComponent
{
public:
	AttackMeshComponent(class GameObject* _owner, class SkeletalMeshComponent* _skMesh, const char* _AttachBoneName);
	~AttackMeshComponent();

	int GetAttackBoneIndex() { return mAttackBoneIndex; };

	void SetOffsetPosition(class Vector3& _offset);
	void SetOffsetRotation(class Vector3& _rotation);

	void Draw(class Shader* _shader)override;
	const Vector3& GetAttachPosisiton()const { return mComputeAttachPos; }
	const Matrix4& GetAttachTransMatrix()const { return mComputeTransMatrix; }
protected:
	Matrix4                      mOffsetPos;
	Matrix4                      mOffsetRotation;
	Matrix4                      mComputeTransMatrix;
	int                          mAttackBoneIndex;
	Vector3                      mComputeAttachPos;
	class SkeletalMeshComponent* mAttackSkeletalMesh;

};