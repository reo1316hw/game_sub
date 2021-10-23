#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> 親クラスのポインタ </param>
CubeMapComponent::CubeMapComponent(GameObject* _owner)
	: Component(_owner)
	, mTexture(nullptr)
	, mLuminance(1.0f)
	, mIsVisible(true)
{
}

/// <summary>
/// デストラクタ
/// </summary>
CubeMapComponent::~CubeMapComponent()
{
	delete mTexture;
}

/// <summary>
/// texture生成処理
/// </summary>
/// <param name="_TextureName"> 使用するtextureのファイルパス </param>
void CubeMapComponent::CreateTexture(const std::string& _TextureName)
{
	mTexture = new Texture();
	mTexture->LoadCubeMap(_TextureName);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="_shader"> 使用するシェーダークラスのポインタ </param>
void CubeMapComponent::Draw(Shader*_shader)
{
	// 透明にしていなければ
	if (mIsVisible)
	{
		// 深度設定
		glDepthFunc(GL_LEQUAL);
		// 輝度情報をシェーダに渡す
		_shader->SetFloatUniform("u_skyLuminance", mLuminance);
		// テクスチャバインド
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, mTexture->GetTextureID());
		// キューブマップ用頂点配列のアクティブ化
		RENDERER->GetCubeMapVerts()->SetActive();
		// 描画
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 念のためバインド解除
		glBindVertexArray(0);

		glDepthFunc(GL_LESS);
	}
}