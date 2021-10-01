#pragma once

/// <summary>
/// �X�P���^�����b�V���̊֐߂Ɏ��t���\�ȃ��b�V��
/// </summary>
class AttackMeshComponent : public MeshComponent
{
public:

	AttackMeshComponent(class GameObject* _owner, class SkeletalMeshComponent* _skMesh, const char* _AttachBoneName);
	~AttackMeshComponent();

	int GetAttackBoneIndex() { return mAttackBoneIndex; };
	void SetAttackBoneIndex(int _attackBoneIndex) { mAttackBoneIndex = _attackBoneIndex; };

	void SetOffsetPosition(class Vector3& _offset);
	void SetOffsetRotation(class Vector3& _rotation);

	void Draw(class Shader* _shader)override;
	const Vector3& GetAttachPosisiton()const { return mComputeAttachPos; }
	const Matrix4& GetAttachTransMatrix()const { return mComputeTransMatrix; }

protected:

	Matrix4                      mOffsetPos;
	Matrix4                      mOffsetRotation;
	Matrix4                      mComputeTransMatrix;
	int                          mAttackBoneIndex;			//gpSkel�t�@�C���̉��Ԗڂ̃{�[����
	Vector3                      mComputeAttachPos;
	class SkeletalMeshComponent* mAttackSkeletalMesh;
};