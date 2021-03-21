#include "MeshComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "Shader.h"
#include "Mesh.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "Texture.h"

/*
@param _skelton スケルトンデータを用いるか。
@sa SkeletalMeshComponent.h
*/
MeshComponent::MeshComponent(GameObject* _owner, bool _skelton)
	:Component(_owner)
	, mMesh(nullptr)
	, textureIndex(0)
	, visible(true)
	,isSkelton(_skelton)
{
	//レンダラーにポインターを送る
	RENDERER->AddMeshComponent(this);
}

MeshComponent::~MeshComponent()
{
	//レンダラーからポインタを削除する
	RENDERER->RemoveMeshComponent(this);
}

/*
@brief　描画処理
@param	_shader 使用するシェーダークラスのポインタ
*/
void MeshComponent::Draw(Shader* _shader)
{
	if (mOwner->GetState() != State::Dead)
	{
		if (mMesh)
		{
			// Set the world transform
			_shader->SetMatrixUniform("uWorldTransform",
				mOwner->GetWorldTransform());
			// Set specular power
			_shader->SetFloatUniform("uSpecPower", mMesh->GetSpecPower());

			_shader->SetFloatUniform("uLuminance", mMesh->GetLuminace());

			_shader->SetFloatUniform("uAlpha", mMesh->GetAlpha());
			// Set the active texture

			// メッシュに定義されているテクスチャをセット
			SetTextureToShader(_shader);

			// Set the argMesh's vertex array as active
			VertexArray* va = mMesh->GetVertexArray();
			va->SetActive();
			// Draw
			glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
		}
	}
}

void MeshComponent::SetTextureToShader(Shader* shader)
{
	// メッシュテクスチャセット
	int texID, stageCount = 0;
	texID = mMesh->GetTextureID(TextureStage::DiffuseMap); // ディフューズ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		shader->SetIntUniform("uDiffuseMap", stageCount);
		stageCount++;
	}
	texID = mMesh->GetTextureID(TextureStage::NormalMap); // 法線マップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		shader->SetIntUniform("uNormalMap", stageCount);
		stageCount++;
	}
	texID = mMesh->GetTextureID(TextureStage::SpecularMap); // スペキュラーマップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		shader->SetIntUniform("uSpecularMap", stageCount);
		stageCount++;
	}
	texID = mMesh->GetTextureID(TextureStage::EmissiveMap); // 自己放射マップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		shader->SetIntUniform("uEmissiveMap", stageCount);
		stageCount++;
	}
}
