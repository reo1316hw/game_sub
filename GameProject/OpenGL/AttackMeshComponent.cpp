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

		//// アタッチ位置算出＆更新
		//Vector3 pos(0, 0, 0);
		//mComputeAttachPos = Vector3::Transform(pos, finalMat);
		//mComputeTransMatrix = finalMat;

		Matrix4 animationMat;
		mAttackSkeletalMesh->GetMatrixFromBoneIndex(animationMat, mAttackBoneIndex);

		shader->SetMatrixUniform("uWorldTransform", mOwner->GetWorldTransform());

		// Set specular power　スペキュラ強度セット
		shader->SetFloatUniform("uSpecPower", 100);

		SetTextureToShader(shader);

		// Set the mesh's vertex array as active　頂点配列をアクティブに
		VertexArray* va = mMesh->GetVertexArray();
		va->SetActive();

		// Draw　描画するー
		glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
	}
}
