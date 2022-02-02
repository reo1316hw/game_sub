#pragma once

class GameObject;
class Shader;
class SkeletalMeshComponent;

/// <summary>
/// �X�P���^�����b�V���̊֐߂Ɏ��t���\�ȃ��b�V��
/// </summary>
class AttackMeshComponent : public MeshComponent
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner"> �e�N���X�̃|�C���^ </param>
	/// <param name="_skMesh"></param>
	/// <param name="_AttachBoneName"></param>
	AttackMeshComponent(GameObject* _owner, SkeletalMeshComponent* _skMesh, const char* _AttachBoneName);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~AttackMeshComponent() {};

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="_shader"> �g�p����V�F�[�_�[�N���X�̃|�C���^ </param>
	void Draw(Shader* _shader)override;
	
protected:

	// gpSkel�t�@�C���̔C�ӂ̃{�[��
	int mAttackBoneIndex;

	// �A�^�b�`�������W
	Vector3                      mComputeAttachPos;
	// �A�^�b�`�������[���h�s��
	Matrix4                      mComputeTransMatrix;
	// �����̕��s�ړ��s��
	Matrix4                      mOffsetPos;
	// �����̉�]�s��
	Matrix4                      mOffsetRotation;

	// �X�P���g�����b�V���̃|�C���^
	SkeletalMeshComponent* mAttackSkeletalMesh;

public:// �Q�b�^�[�Z�b�^�[

	/// <summary>
	/// �A�^�b�`�������W���擾
	/// </summary>
	/// <returns> �A�^�b�`�������W </returns>
	const Vector3& GetAttachPosisiton()const { return mComputeAttachPos; }

	/// <summary>
	/// �A�^�b�`�������[���h�s����擾
	/// </summary>
	/// <returns> �A�^�b�`�������[���h�s�� </returns>
	const Matrix4& GetAttachTransMatrix()const { return mComputeTransMatrix; }

	/// <summary>
	/// gpSkel�t�@�C���̔C�ӂ̃{�[�����擾
	/// </summary>
	/// <returns> gpSkel�t�@�C���̔C�ӂ̃{�[�� </returns>
	int GetAttackBoneIndex() { return mAttackBoneIndex; }

	/// <summary>
	/// gpSkel�t�@�C���̔C�ӂ̃{�[����ݒ�
	/// </summary>
	/// <param name="_attackBoneIndex"> gpSkel�t�@�C���̔C�ӂ̃{�[�� </param>
	void SetAttackBoneIndex(int _attackBoneIndex) { mAttackBoneIndex = _attackBoneIndex; }

	/// <summary>
	/// �����̕��s�ړ��s���ݒ�
	/// </summary>
	/// <param name="_Offset"> �����̕��s�ړ��s�� </param>
	void SetOffsetPosition(const Vector3& _Offset);

	/// <summary>
	/// �����̉�]�s���ݒ�
	/// </summary>
	/// <param name="_Rotation"> �����̉�]�s�� </param>
	void SetOffsetRotation(const Vector3& _Rotation);
};