#pragma once

class SkeletalMeshComponent;

/// <summary>
/// �X�P���^�����b�V���̊֐߂Ɏ��t���\�ȃ��b�V��
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

	//gpSkel�t�@�C���̉��Ԗڂ̃{�[����
	int mAttackBoneIndex;

	SkeletalMeshComponent* mAttackSkeletalMesh;

	GameObject* mOwner;
};