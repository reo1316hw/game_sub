#pragma once

/*
 @file CubeMapComponent.h
 @brief キューブマップの管理と描画を行う
*/
class CubeMapComponent : public Component
{
public:

	/*
	@fn コンストラクタ
	@param _owner 親クラスのポインタ
	*/
	CubeMapComponent(GameObject* _owner);

	/*
	@fn デストラクタ
	@brief  Componentの削除を行う
	*/
	~CubeMapComponent();

	/*
	@brief　texture生成処理
	@param	_TextureName 使用するtextureのファイルパス
	*/
	void CreateTexture(const std::string& _TextureName);

	/*
	@brief　描画処理
	@param	in_shader 使用するシェーダークラスのポインタ
	*/
	void Draw(Shader* _shader);

	/*
	@brief　スカイボックスに使用しているtextureのgetter
	@param	texture 使用しているtextureクラスのポインタ
	*/
	class Texture* GetSkyBoxTexture() { return mTexture; }

	// キューブを表示するかしないかのセット
	void SetIsVisible(bool _isVisible) { mIsVisible = _isVisible; }

	// 輝度情報のセット
	void SetLuminance(float _luminance) { mLuminance = _luminance; }


private:

	// textureクラスのポインタ
	Texture* mTexture;

	// 輝度情報
	float mLuminance;

	// 描画するかしないかのフラグ
	bool mIsVisible;

};

