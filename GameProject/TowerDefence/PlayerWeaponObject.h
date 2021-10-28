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
    /// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	PlayerWeaponObject(SkeletalMeshComponent* _skMesh, const std::string _GpmeshName, const Tag& _ObjectTag, PlayerObject* _playerPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerWeaponObject() {};

private:

	// ���̏�����]�l
	const Vector3 MSwordRot;
	// ���̏������W
	const Vector3 MSwordPos;

	// ���탁�b�V��
	AttackMeshComponent* mWeaponMesh;
};