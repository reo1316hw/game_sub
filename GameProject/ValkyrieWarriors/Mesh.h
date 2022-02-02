#pragma once

// 前方宣言
class Renderer;
class VertexArray;
class Texture;

enum class TextureStage;

	/*
@file Mesh.h
@brief メッシュデータ
*/
class Mesh
{
public:
    Mesh();
    ~Mesh();
	/*
	@brief  メッシュデータの読み込み
	@param	_fileName ロードしたいメッシュのファイル名
	@param	_renderer Rendererクラスのポインタ
	@return true : 成功 , false : 失敗
	*/
    bool Load(const std::string& _fileName, Renderer* _renderer);

	/*
	@brief  ロードしたメッシュデータの解放
	*/
    void Unload();
private:
    //このメッシュに使うテクスチャのポインタの可変長コンテナ
    std::vector<Texture*> mTextures;
	//このメッシュに使う頂点データ
	std::vector<Vector3> mVerts;
	//クラスのポインタ
    VertexArray* mVertexArray;

    //このメッシュに使うシェーダーの名前
    std::string mShaderName;
    //オブジェクト空間での境界球の半径
    float mRadius;
    //鏡面反射成分の大きさ
    float mSpecPower;
	// 自己発光強度(HDR)
	float mLuminance;
	// 透明度
	float mAlpha;
	// 矩形当たり判定
	AABB mBox;

	// テクスチャステージに割り当てられたテクスチャ
	std::unordered_map<TextureStage, int> mStageDefTexture;

public://ゲッターセッター
	/*
	@return	VertexArray型のポインタ
	*/
	VertexArray* GetVertexArray() { return mVertexArray; }

	/*
	@return Textureクラスのポインタ
	*/
	Texture* GetTexture(size_t _index);

	int GetTextureID(TextureStage _stage);

	/*
	@return Textureクラスのポインタ
	*/
	const std::string& GetShaderName() const { return mShaderName; }

	/*
	@return 半径
	*/
	float GetRadius() const { return mRadius; }

	/*
	@return 鏡面反射成分
	*/
	float GetSpecPower() const { return mSpecPower; }

	/*
	@return 自己発光強度
	*/
	float GetLuminace() const { return mLuminance; }

	/*
	@return 透明度
	*/
	float GetAlpha() const { return mAlpha; }

	const AABB& GetBox() const { return mBox; }

	/*
	@return 頂点データ
	*/
	std::vector<Vector3> GetVerts() { return mVerts; }
};