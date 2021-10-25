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

	/// <summary>
	/// �I�u�W�F�N�g�̍X�V����
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void UpdateGameObject(float _deltaTime)override;

	/// <summary>
    /// �q�b�g�������m�F
    /// </summary>
    /// <returns> �q�b�g������ </returns>
	bool IsHitCheck() { return mIsHit == true; }

private:

	/// <summary>
    /// �q�b�g�������̏���
    /// </summary>
    /// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
	void OnCollision(const GameObject& _HitObject)override;

	// �q�b�g�t���O��L���ɂ���^�C�~���O
	const int MEnableIsHitTiming;
	// ���̏�����]�l
	const Vector3 MSwordRot;
	// ���̏������W
	const Vector3 MSwordPos;

	// �q�b�g������
	bool mIsHit;
	// �q�b�g�t���O�𖳌��ɂ���t���O
	bool mDisableIsHit;

	// �q�b�g�t���O�𖳌�����
	int mIsHitDisableCount;

	// ���탁�b�V��
	AttackMeshComponent* mWeaponMesh;
	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
};