#include "pch.h"

AttackMeshComponent::AttackMeshComponent(GameObject* _owner, SkeletalMeshComponent* _skMesh, const char* _AttachBoneName)
	: MeshComponent(_owner)
	, mAttackBoneIndex(0)
	, mAttackSkeletalMesh(_skMesh)
{
	mAttackBoneIndex = _skMesh->GetBoneIndexFromName(_AttachBoneName);
	//printf("Create : AttachMeshComponent [%d]\n", mID);
}

AttackMeshComponent::~AttackMeshComponent()
{
	//printf("Remove : AttachMeshComponent [%d]\n", mID);
}

void AttackMeshComponent::SetOffsetPosition(const Vector3& offset)
{
	mOffsetPos = Matrix4::CreateTranslation(offset);
}

void AttackMeshComponent::SetOffsetRotation(const Vector3& rotation)
{
	mOffsetRotation = Matrix4::CreateRotationY(rotation.y)
		* Matrix4::CreateRotationX(rotation.x)
		* Matrix4::CreateRotationZ(rotation.z);
}

void AttackMeshComponent::Draw(Shader* shader)
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

		// Set the active texture�@�A�N�e�B�u�e�N�X�`���Z�b�g
		//Texture* t = mMesh->GetTexture(mTextureIndex);
		//if (t)
		//{
		//	t->SetActive();
		//}

		SetTextureToShader(shader);

		// Set the mesh's vertex array as active�@���_�z����A�N�e�B�u��
		VertexArray* va = mMesh->GetVertexArray();
		va->SetActive();

		// Draw�@�`�悷��[
		glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
	}
}
