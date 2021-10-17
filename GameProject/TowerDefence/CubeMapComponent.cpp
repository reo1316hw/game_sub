#include "pch.h"

/*
@fn コンストラクタ
@param _owner 親クラスのポインタ
*/
CubeMapComponent::CubeMapComponent(GameObject* _owner)
	: Component(_owner)
	, mTexture(nullptr)
	, mLuminance(1.0f)
	, mIsVisible(true)
{
}

/*
@fn デストラクタ
@brief  Componentの削除を行う
*/
CubeMapComponent::~CubeMapComponent()
{
	delete mTexture;
}

/*
@brief　texture生成処理
@param	_TextureName 使用するtextureのファイルパス
*/
void CubeMapComponent::CreateTexture(const std::string& _TextureName)
{
	mTexture = new Texture();
	mTexture->LoadCubeMap(_TextureName);
}

/*
@brief　描画処理
@param	in_shader 使用するシェーダークラスのポインタ
*/
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