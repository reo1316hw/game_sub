#pragma once

/// <summary>
/// �v���C���[�̕���
/// </summary>
class PlayerWeaponObject : public GameObject
{
public:

	PlayerWeaponObject(GameObject* _owner, SkeletalMeshComponent* _skMesh, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	~PlayerWeaponObject() {};

	void UpdateGameObject(float _deltaTime)override;

private:

	void OnCollision(const GameObject& _hitObject)override;

	// ���̏�����]�l
	const Vector3 MSwordRot;
	// ���̏������W
	const Vector3 MSwordPos;
	// ���̃A�^�b�`����Ă�����W
	Vector3 mComputeAttachPos;

	//gpSkel�t�@�C���̉��Ԗڂ̃{�[����
	int mAttackBoneIndex;

	Matrix4 mOffsetPos;
	Matrix4 mOffsetRotation;

	// �A�^�b�`����Ă���I�u�W�F�N�g
	GameObject* mOwner;

	// SkeletalMeshComponent�|�C���^
	SkeletalMeshComponent* mAttackSkeletalMesh;
	// ����̋��󓖂��蔻��
	Sphere mWeaponSphere;
	// ���탁�b�V��
	MeshComponent* mWeaponMesh;
	// ����̓����蔻��
	SphereCollider* mSphereCollider;

public:// �Q�b�^�[�Z�b�^�[

	int GetAttackBoneIndex() { return mAttackBoneIndex; };
	void SetAttackBoneIndex(int _attackBoneIndex) { mAttackBoneIndex = _attackBoneIndex; };

	const Vector3& GetAttachPosisiton()const { return mComputeAttachPos; }
};

