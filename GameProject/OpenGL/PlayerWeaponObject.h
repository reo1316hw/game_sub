#pragma once

/// <summary>
/// �v���C���[�̕���
/// </summary>
class PlayerWeaponObject : public GameObject
{
public:

	PlayerWeaponObject(GameObject* _owner, SkeletalMeshComponent* _skMesh, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	~PlayerWeaponObject() {};

	void AddAttackHitSphere(const float _Scale = 1.0f);
	void RemoveAttackHitSphere();

	void UpdateGameObject(float _deltaTime)override;

private:

	void OnCollision(const GameObject& _hitObject)override;

	// ���̏�����]�l
	const Vector3 MSwordRot;
	// ���̏������W
	const Vector3 MSwordPos;

	// ����̋��󓖂��蔻��
	Sphere mWeaponSphere;
	// �A�^�b�`����Ă���I�u�W�F�N�g
	GameObject* mOwner;
	// ���탁�b�V��
	AttackMeshComponent* mWeaponMesh;
	// ���̓����蔻����s���R���|�[�l���g�̃|�C���^
	SphereCollider* mSphereCollider;
};


