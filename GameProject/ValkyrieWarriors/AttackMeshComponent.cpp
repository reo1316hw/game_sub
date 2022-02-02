#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> 親クラスのポインタ </param>
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
/// 描画
/// </summary>
/// <param name="_shader"> 使用するシェーダークラスのポインタ </param>
void AttackMeshComponent::Draw(Shader* shader)
{
	if (mOwner->GetState() != State::eDead)
	{
		if (mMesh)
		{
			Matrix4 finalMat, animationMat;
			mAttackSkeletalMesh->GetMatrixFromBoneIndex(animationMat, mAttackBoneIndex);
			finalMat = mOffsetRotation * mOffsetPos * animationMat;

			// アタッチ位置算出＆更新
			Vector3 pos(0, 0, 0);
			mComputeAttachPos = Vector3::Transform(pos, finalMat);
			mComputeTransMatrix = finalMat;

			shader->SetMatrixUniform("uWorldTransform", finalMat);

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
}

/// <summary>
/// 差分の平行移動行列を設定
/// </summary>
/// <param name="_Offset"> 差分の平行移動行列 </param>
void AttackMeshComponent::SetOffsetPosition(const Vector3& _Offset)
{
	mOffsetPos = Matrix4::CreateTranslation(_Offset);
}

/// <summary>
/// 差分の回転行列を設定
/// </summary>
/// <param name="_Rotation"> 差分の回転行列 </param>
void AttackMeshComponent::SetOffsetRotation(const Vector3& _Rotation)
{
	mOffsetRotation = Matrix4::CreateRotationY(_Rotation.y)
		* Matrix4::CreateRotationX(_Rotation.x)
		* Matrix4::CreateRotationZ(_Rotation.z);
}