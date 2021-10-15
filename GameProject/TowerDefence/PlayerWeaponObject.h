#pragma once

/// <summary>
/// �v���C���[�̕���
/// </summary>
class PlayerWeaponObject : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_skMesh"> �e�N���X�̃X�P���g�����b�V���̃|�C���^ </param>
	/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	PlayerWeaponObject(SkeletalMeshComponent* _skMesh, const std::string _GpmeshName, const Tag& _ObjectTag);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerWeaponObject() {};

	/// <summary>
	/// �I�u�W�F�N�g�̍X�V����
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	/// <summary>
    /// �q�b�g�������̏���
    /// </summary>
    /// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
	void OnCollision(const GameObject& _HitObject)override;

	// ���̏�����]�l
	const Vector3 MSwordRot;
	// ���̏������W
	const Vector3 MSwordPos;

	// ���탁�b�V��
	AttackMeshComponent* mWeaponMesh;
};


