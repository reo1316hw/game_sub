#pragma once

class SkeletalMeshComponent;

/// <summary>
/// スケルタルメッシュの関節に取り付け可能なメッシュ
/// </summary>
class AttackMeshComponent : public MeshComponent
{
public:

	AttackMeshComponent(class GameObject* _owner, class SkeletalMeshComponent* _skMesh, const char* _AttachBoneName);
	~AttackMeshComponent() {};

	int GetAttackBoneIndex() { return mAttackBoneIndex; };
	void SetAttackBoneIndex(int _attackBoneIndex) { mAttackBoneIndex = _attackBoneIndex; };

	void Draw(class Shader* _shader)override;

protected:

	//gpSkelファイルの何番目のボーンか
	int mAttackBoneIndex;

	SkeletalMeshComponent* mAttackSkeletalMesh;

	GameObject* mOwner;
};