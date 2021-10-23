#pragma once
#include <SDL.h>
#include <unordered_map>
#include <vector>
#include <string>
#include "Math.h"
#include "ParticleComponent.h"
#define RENDERER Renderer::GetInstance()

//平行光源用の構造体
struct DirectionalLight
{
	// 光の方向
	Vector3 m_direction;
	// 拡散反射色
	Vector3 m_diffuseColor;
	// 鏡面反射色
	Vector3 m_specColor;
};

enum class TextureStage
{
	DiffuseMap,
	NormalMap,
	SpecularMap,
	EmissiveMap,
	ShadowMap,
};

// 前方宣言
class SpriteComponent;
class Texture;
class Mesh;
class Game;
class MeshComponent;
class InvisibleMeshComponent;
class Shader;
class VertexArray;
class ParticleComponent;
class HDRRenderer;
class CubeMapComponent;
class PlayerObject;

/*
@file Renderer.h
@brief 描画の進行を行うクラス
*/
class Renderer
{
public:
	/*
	@brief  インスタンスを取得する
	@return Rendererクラスのインスタンス
	*/
	static Renderer* GetInstance() { return mRenderer; }

	/*
	@brief  インスタンスを作成する
	*/
	static void CreateInstance();

	/*
	@brief  インスタンスを削除する
	*/
	static void DeleteInstance();

	/*
	@brief  初期化処理
	@return true : 成功 , false : 失敗
	*/
	bool Initialize(float _screenWidth, float _screenHeight, bool _fullScreen);
	/*
	@brief  終了処理
	*/
	void Shutdown();

	/*
	@brief  ロードしたデータの解放
	*/
	void UnloadData();

	/*
	@brief  描画処理
	*/
	void Draw();

	/*void DrawTexture(class Texture* texture, const Vector2& offset = Vector2::Zero, float scale = 1.0f, float alpha = 1.0f);*/
	   
	/*
	@brief  スプライトの追加
	@param	_spriteComponent　追加するSpriteComponentクラスのポインタ
	*/
	void AddSprite(SpriteComponent* _spriteComponent);

	/*
	@brief スプライトの削除
	@param	_spriteComponent　削除するSpriteComponentクラスのポインタ
	*/
	void RemoveSprite(SpriteComponent* _spriteComponent);

	/*
	@brief  パーティクルの追加
	@param	_particleComponent　追加するParticleObjectクラスのポインタ
	*/
	void AddParticle(ParticleComponent* _particleComponent);

	/*
	@brief  スプライトの削除
	@param	削除するParticleObjectクラスのポインタ
	*/
	void RemoveParticle(ParticleComponent* _particleComponent);
	
	/*
	@brief  メッシュコンポーネントの追加
	@param	_meshComponent　追加するMeshComponentクラスのポインタ
	*/
	void AddMeshComponent(MeshComponent* _meshComponent);

	/*
	@brief  メッシュコンポーネントの削除
	@param	_meshComponent　削除するMeshComponentクラスのポインタ
	*/
	void RemoveMeshComponent(MeshComponent* _meshComponent);

	/*
	@brief  メッシュコンポーネントの追加
	@param	_meshComponent　追加するMeshComponentクラスのポインタ
	*/
	void AddInvisibleMeshComponent(InvisibleMeshComponent* _invisibleMeshComponent);

	/*
	@brief  メッシュコンポーネントの削除
	@param	_meshComponent　削除するMeshComponentクラスのポインタ
	*/
	void RemoveInvisibleMeshComponent(InvisibleMeshComponent* _invisibleMeshComponent);


	/*
	@brief  テクスチャの取得
	@param	_fileName　取得したいテクスチャのファイル名
	@return Textureクラスのポインタ
	*/
	Texture* GetTexture(const std::string& _fileName);
	   
	/*
	@param _fileName モデルへのアドレス
	@return スケルトンモデルの取得
	*/
	const class Skeleton* GetSkeleton(const char* _fileName);                       
	/*
	@param _fileName アニメーションへのアドレス
	@return スケルトンアニメーションの取得
	*/
	const class Animation* GetAnimation(const char* _fileName, bool _loop);                     // スケルタルアニメーションの取得

	/*
	@brief  メッシュの取得
	@param	_fileName 取得したいメッシュのファイル名
	@return Meshクラスのポインタ
	*/
	Mesh* GetMesh(const std::string& _fileName);

	/*
	@brief	ビュー行列を設定する
	@param	_view ビュー行列
	*/
	void SetViewMatrix(const Matrix4& _view) { mView = _view; }

	/*
	@brief	環境光を設定する
	@param	_ambient Vector3（環境光を表す）
	*/
	void SetAmbientLight(const Vector3& _ambient) { mAmbientLight = _ambient; }

	/*
	@brief	平行光源の構造体を取得する
	@return	DirectionalLight（平行光源の構造体）
	*/
	DirectionalLight& GetDirectionalLight() { return mDirLight; }

	/*
	@brief	スクリーンの横幅を取得する
	@return	スクリーンの横幅
	*/
	float GetScreenWidth() const { return mScreenWidth; }

	/*
	@brief	スクリーンの縦幅を取得する
	@return	スクリーンの縦幅
	*/
	float GetScreenHeight() const { return mScreenHeight; }

	Matrix4 GetViewMatrix() const { return mView; }

	void SetParticleVertex();

	Matrix4 GetProjectionMatrix() { return mProjection; }

	SDL_Renderer* GetSDLRenderer() { return mSdlRenderer; }

	unsigned int GetUndefineTexID() { return mUndefineTexID; }

	// スカイボックスをアクティブにする
	void SetActiveSkyBox(CubeMapComponent* _activeSkyBox) { mActiveSkyBox = _activeSkyBox; }

	VertexArray* GetCubeMapVerts() { return mCubeVerts; }

	/*
    @brief キューブマップ(スカイボックス用)頂点配列定義
    */
	void CreateCubeVerts();

	/*void DrawTexture(Texture* texture, const Vector2& offset, float scale = 1.0f, float alpha = 1.0f);
	void DrawTexture(class Texture* texture, int index, int xDyvNum, int yDivNum, const Vector2& offset, float scale = 1.0f, float alpha = 1.0f);*/

private:
	//コンストラクタ、デストラクタの隠蔽
	Renderer();
	~Renderer();

	// スケルトンデータ
	std::unordered_map<std::string, class Skeleton*> mSkeletons;
	// アニメーションデータ
	std::unordered_map<std::string, class Animation*> mAnims;    
	// スケルトンメッシュの描画に使われる
	std::vector<class SkeletalMeshComponent*>       mSkeletalMeshes;   

	//自分のインスタンス
	static Renderer* mRenderer;
	SDL_Renderer* mSdlRenderer;

	/*
	@brief  シェーダーの読み込み
	@return true : 成功 , false : 失敗
	*/
	bool LoadShaders();
	/*
	@brief  Sprite用の頂点バッファとインデックスバッファの作成
	*/
	void CreateSpriteVerts();
	void CreateParticleVerts();

	void DrawParticle();

	void Draw3DScene(unsigned int _framebuffer, const Matrix4& _view, const Matrix4& _proj,
		float _viewPortScale = 1.0f, bool _lit = true);

	/*
	@brief  光源情報をシェーダーの変数にセットする
	@param  _shader セットするShaderクラスのポインタ
	*/
	void SetLightUniforms(Shader* _shader, const Matrix4& _view);

	void ChangeBlendMode(ParticleComponent::ParticleBlendType _blendType);
	void ChangeTexture(int _changeTextureID);

	Vector3 CalcCameraPos();

	//ファイル名でメッシュを取得するための連想配列
	std::unordered_map<std::string, Mesh*> mMeshes;
	//メッシュコンポーネントのポインタの可変長コンテナ
	std::vector<MeshComponent*> mMeshComponents;
	//インビジブルメッシュコンポーネントのポインタの可変長コンテナ
	std::vector<InvisibleMeshComponent*> mInvisibleMeshComponents;
	//スプライトコンポーネントのポインタの可変長コンテナ
	std::vector<SpriteComponent*> mSprites;
	//パーティクルのポインタ
	std::vector<ParticleComponent*> mParticles;
	//ファイル名でテクスチャを取得するための連想配列
	std::unordered_map<std::string, Texture*>mTextures;

	//クラスのポインタ
	//スプライト
	Shader* mSpriteShader;
	VertexArray* mSpriteVerts;
	//UI
	Shader* mUiShader;
	VertexArray* mUiVerts;
	//メッシュ
	Shader* mMeshShader;
	//スキンメッシュ
	Shader*  mSkinnedShader;  
	//インビジブルメッシュ
	Shader* mInvisibleMeshShader;
	Shader* mBasicShader;
	//パーティクル
	Shader* mParticleShader;

	// スカイボックス
	Shader* mSkyBoxShader;
	// パーティクル用頂点定義
	VertexArray* mParticleVertex;
	// プレイヤー
	PlayerObject* mPlayer;

	// HDR レンダラー
	HDRRenderer* mHDRRenderer;
	// キューブマップ
	CubeMapComponent* mActiveSkyBox; // 有効な(描画する)スカイボックス
	// キューブ頂点配列
	VertexArray* mCubeVerts;


	//ビュー行列
	Matrix4 mView;
	//射影行列
	Matrix4 mProjection;
	//ビルボード行列
	Matrix4 mBillboardMat;
	//スクリーンの横幅
	float mScreenWidth;
	//スクリーンの縦幅
	float mScreenHeight;
	//環境光
	Vector3 mAmbientLight;
	//平行光源
	DirectionalLight mDirLight;
	//ウィンドウ
	SDL_Window* mWindow;
	//コンテキスト
	SDL_GLContext mContext;
	// UIの初期座標に加算される座標
	Vector2 mAddPosition;

	// 未設定テクスチャの場合に割り当てられる黒色テクスチャ
	unsigned int mUndefineTexID;
};