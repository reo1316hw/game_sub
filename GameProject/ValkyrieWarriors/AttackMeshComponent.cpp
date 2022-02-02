#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �e�N���X�̃|�C���^ </param>
/// <param name="_skMesh"></param>
/// <param name="_AttachBoneName"></param>
AttackMeshComponent::AttackMeshComponent(GameObject* _owner, SkeletalMeshComponent* _skMesh, const char* _AttachBoneName)
	: MeshComponent(_owner)
	, mAttackBoneIndex(0)
	, mAttackSkeletalMesh(_skMesh)
{
	mAttackBoneIndex = _skMesh->GetBoneIndexFromName(_AttachBoneName);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="_shader"> �g�p����V�F�[�_�[�N���X�̃|�C���^ </param>
void AttackMeshComponent::Draw(Shader* shader)
{
	if (mOwner->GetState() != State::eDead)
	{
		if (mMesh)
		{
			Matrix4 finalMat, animationMat;
			mAttackSkeletalMesh->GetMatrixFromBoneIndex(animationMat, mAttackBoneIndex);
			finalMat = mOffsetRotation * mOffsetPos * animationMat;

			// �A�^�b�`�ʒu�Z�o���X�V
			Vector3 pos(0, 0, 0);
			mComputeAttachPos = Vector3::Transform(pos, finalMat);
			mComputeTransMatrix = finalMat;

			shader->SetMatrixUniform("uWorldTransform", finalMat);

			// Set specular power�@�X�y�L�������x�Z�b�g
			shader->SetFloatUniform("uSpecPower", 100);

			SetTextureToShader(shader);

			// Set the mesh's vertex array as active�@���_�z����A�N�e�B�u��
			VertexArray* va = mMesh->GetVertexArray();
			va->SetActive();

			// Draw�@�`�悷��[
			glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
		}
	}
}

/// <summary>
/// �����̕��s�ړ��s���ݒ�
/// </summary>
/// <param name="_Offset"> �����̕��s�ړ��s�� </param>
void AttackMeshComponent::SetOffsetPosition(const Vector3& _Offset)
{
	mOffsetPos = Matrix4::CreateTranslation(_Offset);
}

/// <summary>
/// �����̉�]�s���ݒ�
/// </summary>
/// <param name="_Rotation"> �����̉�]�s�� </param>
void AttackMeshComponent::SetOffsetRotation(const Vector3& _Rotation)
{
	mOffsetRotation = Matrix4::CreateRotationY(_Rotation.y)
		* Matrix4::CreateRotationX(_Rotation.x)
		* Matrix4::CreateRotationZ(_Rotation.z);
}