#include "pch.h"

AttackMeshComponent::AttackMeshComponent(GameObject* _owner, SkeletalMeshComponent* _skMesh, const char* _AttachBoneName)
	: MeshComponent(_owner)
	, mAttackBoneIndex(0)
	, mAttackSkeletalMesh(_skMesh)
	, mOwner(_owner)
{
	mAttackBoneIndex = _skMesh->GetBoneIndexFromName(_AttachBoneName);
}

void AttackMeshComponent::Draw(Shader* shader)
{
	if (mMesh)
	{
		//Matrix4 finalMat, animationMat;
		//mAttackSkeletalMesh->GetMatrixFromBoneIndex(animationMat, mAttackBoneIndex);
		//finalMat = mOffsetRotation * mOffsetPos * animationMat;

		//// �A�^�b�`�ʒu�Z�o���X�V
		//Vector3 pos(0, 0, 0);
		//mComputeAttachPos = Vector3::Transform(pos, finalMat);
		//mComputeTransMatrix = finalMat;

		Matrix4 animationMat;
		mAttackSkeletalMesh->GetMatrixFromBoneIndex(animationMat, mAttackBoneIndex);

		shader->SetMatrixUniform("uWorldTransform", mOwner->GetWorldTransform());

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
