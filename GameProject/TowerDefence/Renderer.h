#pragma once
#include <SDL.h>
#include <unordered_map>
#include <vector>
#include <string>
#include "Math.h"
#include "ParticleComponent.h"

#define RENDERER Renderer::GetInstance()

/// <summary>
/// 平行光源用の構造体
/// </summary>
struct DirectionalLight
{
	// 光の方向
	Vector3 m_direction;
	// 拡散反射色
	Vector3 m_diffuseColor;
	// 鏡面反射色
	Vector3 m_specColor;
};

/// <summary>
/// テクスチャステージ
/// </summary>
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

/// <summary>
/// 描画の進行を行うクラス
/// </summary>
class Renderer
{
public:

	/// <summary>
	/// インスタンスを作成する
	/// </summary>
	static void CreateInstance();

	/// <summary>
	/// インスタンスを削除する
	/// </summary>
	static void DeleteInstance();

	/*
	@brief  初期化処理
	@return true : 成功 , false : 失敗
	*/

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="_ScreenWidth"> スクリーンの幅 </param>
	/// <param name="_ScreenHeight"> スクリーンの高さ </param>
	/// <param name="_IsFullScreen"> フルスクリーンにするかのフラグ </param>
	/// <returns> true : 成功 , false : 失敗 </returns>
	bool Initialize(const float& _ScreenWidth, const float& _ScreenHeight, const bool& _IsFullScreen);
	
	/// <summary>
	/// 終了処理
	/// </summary>
	void Shutdown();

	/// <summary>
	/// ロードしたデータの解放
	/// </summary>
	void UnloadData();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// スプライトの追加
	/// </summary>
	/// <param name="_spriteComponent"> 追加するSpriteComponentクラスのポインタ </param>
	void AddSprite(SpriteComponent* _spriteComponent);

	/// <summary>
	/// スプライトの削除
	/// </summary>
	/// <param name="_spriteComponent"> 削除するSpriteComponentクラスのポインタ </param>
	void RemoveSprite(SpriteComponent* _spriteComponent);

	/// <summary>
	/// パーティクルの追加
	/// </summary>
	/// <param name="_particleComponent"> 追加するParticleObjectクラスのポインタ </param>
	void AddParticle(ParticleComponent* _particleComponent);

	/// <summary>
	/// パーティクルの削除
	/// </summary>
	/// <param name="_particleComponent"> 削除するParticleObjectクラスのポインタ </param>
	void RemoveParticle(ParticleComponent* _particleComponent);

	/// <summary>
	/// メッシュコンポーネントの追加
	/// </summary>
	/// <param name="_meshComponent"> 追加するMeshComponentクラスのポインタ </param>
	void AddMeshComponent(MeshComponent* _meshComponent);

	/// <summary>
	/// メッシュコンポーネントの削除
	/// </summary>
	/// <param name="_meshComponent"> 削除するMeshComponentクラスのポインタ </param>
	void RemoveMeshComponent(MeshComponent* _meshComponent);

	/// <summary>
	/// キューブコンポーネントの削除
	/// </summary>
	void RemoveCubeComponent() { mActiveSkyBox = nullptr; };

private:

	/// <summary>
	/// コンストラクタ
	/// 隠蔽
	/// </summary>
	Renderer();

	/// <summary>
	/// デストラクタ
	/// 隠蔽
	/// </summary>
	~Renderer();

	/// <summary>
	/// シェーダーの読み込み
	/// </summary>
	/// <returns> true : 成功 , false : 失敗 </returns>
	bool LoadShaders();

	/// <summary>
	/// スプライト用の頂点バッファとインデックスバッファの作成
	/// </summary>
	void CreateSpriteVerts();

	/// <summary>
	/// パーティクル用の頂点バッファとインデックスバッファの作成
	/// </summary>
	void CreateParticleVerts();

	/// <summary>
	/// キューブマップ(スカイボックス用)頂点配列定義
	/// </summary>
	void CreateCubeVerts();

	/// <summary>
	/// 全てのパーティクルを描画準備
	/// </summary>
	void DrawParticle();

	/// <summary>
	/// 光源情報をシェーダーの変数にセットする
	/// </summary>
	/// <param name="_shader"> セットするShaderクラスのポインタ </param>
	/// <param name="_View"> ビュー行列 </param>
	void SetLightUniforms(Shader* _shader, const Matrix4& _View);

	/// <summary>
	/// ブレンドモードを変更する
	/// </summary>
	/// <param name="_blendType"> ブレンドモード </param>
	void ChangeBlendMode(ParticleComponent::ParticleBlendType _blendType);

	/// <summary>
	/// テクスチャを変更
	/// </summary>
	/// <param name="_ChangeTextureID"> テクスチャID </param>
	void ChangeTexture(const int& _ChangeTextureID);

	/// <summary>
	/// ワールド座標でのカメラ位置算出
	/// </summary>
	/// <returns> カメラ位置(ワールド座標) </returns>
	Vector3 CalcCameraPos();

	// スケルトンデータ
	std::unordered_map<std::string, Skeleton*> mSkeletons;
	// アニメーションデータ
	std::unordered_map<std::string, Animation*> mAnims;
	//ファイル名でメッシュを取得するための連想配列
	std::unordered_map<std::string, Mesh*> mMeshes;
	//ファイル名でテクスチャを取得するための連想配列
	std::unordered_map<std::string, Texture*>mTextures;

	//メッシュコンポーネントのポインタの可変長コンテナ
	std::vector<MeshComponent*> mMeshComponents;
	// スケルトンメッシュの描画に使われる
	std::vector<SkeletalMeshComponent*> mSkeletalMeshes;
	//スプライトコンポーネントのポインタの可変長コンテナ
	std::vector<SpriteComponent*> mSprites;
	//パーティクルのポインタ
	std::vector<ParticleComponent*> mParticles;

	// 未設定テクスチャの場合に割り当てられる黒色テクスチャ
	unsigned int mUndefineTexID;

	// スクリーンの横幅
	float mScreenWidth;
	// スクリーンの縦幅
	float mScreenHeight;

	// UIの初期座標に加算される座標
	Vector2 mAddPosition;

	// 環境光
	Vector3 mAmbientLight;

	// ビュー行列
	Matrix4 mView;
	// 射影行列
	Matrix4 mProjection;
	// ビルボード行列
	Matrix4 mBillboardMat;
	
	
	// 平行光源
	DirectionalLight mDirLight;
	// ウィンドウ
	SDL_Window* mWindow;
	// コンテキスト
	SDL_GLContext mContext;

	// 自分のインスタンス
	static Renderer* mRenderer;

	// レンダラーの状態を含む構造体のポインタ
	SDL_Renderer* mSdlRenderer;
	// スプライト
	Shader* mSpriteShader;
	VertexArray* mSpriteVerts;
	// メッシュ
	Shader* mMeshShader;
	// スキンメッシュ
	Shader*  mSkinnedShader;  
	Shader* mBasicShader;
	// パーティクル
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

public:// ゲッターセッター

	/// <summary>
	/// インスタンスを取得する
	/// </summary>
	/// <returns> Rendererクラスのインスタンス </returns>
	static Renderer* GetInstance() { return mRenderer; }

	/// <summary>
	/// テクスチャを取得
	/// </summary>
	/// <param name="_FileName"> 取得したいテクスチャのファイル名 </param>
	/// <returns> テクスチャクラスのポインタ </returns>
	Texture* GetTexture(const std::string& _FileName);

	/// <summary>
	/// スケルトンモデルを取得
	/// </summary>
	/// <param name="_FileName"> 取得したいスケルトンモデルのファイル名 </param>
	/// <returns> スケルトンクラスのポインタ </returns>
	const Skeleton* GetSkeleton(const char* _FileName);

	/// <summary>
	/// スケルトンアニメーションを取得
	/// </summary>
	/// <param name="_FileName"> 取得したいスケルトンアニメーションのファイル名 </param>
	/// <param name="_Loop"> アニメーションをループさせるか </param>
	/// <returns> アニメーションクラスのポインタ </returns>
	const Animation* GetAnimation(const char* _FileName, const bool& _Loop);

	/// <summary>
	/// メッシュを取得
	/// </summary>
	/// <param name="_FileName"> 取得したいメッシュのファイル名 </param>
	/// <returns> メッシュクラスのポインタ </returns>
	Mesh* GetMesh(const std::string& _FileName);

	/// <summary>
	/// 環境光を設定する
	/// </summary>
	/// <param name="_Ambient"> 環境光 </param>
	void SetAmbientLight(const Vector3& _Ambient) { mAmbientLight = _Ambient; }

	/// <summary>
	/// 平行光源の構造体を取得する
	/// </summary>
	/// <returns> 平行光源の構造体 </returns>
	DirectionalLight& GetDirectionalLight() { return mDirLight; }

	/// <summary>
	/// スクリーンの幅を取得する
	/// </summary>
	/// <returns> スクリーンの幅 </returns>
	float GetScreenWidth() const { return mScreenWidth; }

	/// <summary>
	/// スクリーンの高さを取得する
	/// </summary>
	/// <returns> スクリーンの高さ </returns>
	float GetScreenHeight() const { return mScreenHeight; }

	/// <summary>
	/// ビュー行列を取得する
	/// </summary>
	/// <returns> ビュー行列 </returns>
	Matrix4 GetViewMatrix() const { return mView; }

	/// <summary>
	/// ビュー行列を設定する
	/// </summary>
	/// <param name="_View"> ビュー行列 </param>
	void SetViewMatrix(const Matrix4& _View) { mView = _View; }

	/// <summary>
	/// パーティクルの頂点配列を設定
	/// </summary>
	void SetParticleVertex();

	/// <summary>
	/// プロジェクション行列を取得する
	/// </summary>
	/// <returns> プロジェクション行列 </returns>
	Matrix4 GetProjectionMatrix() { return mProjection; }

	/// <summary>
	/// レンダラーの状態を含む構造体を取得
	/// </summary>
	/// <returns> レンダラーの状態を含む構造体のポインタ </returns>
	SDL_Renderer* GetSDLRenderer() { return mSdlRenderer; }

	/// <summary>
	/// 未設定テクスチャの場合に割り当てられる黒色テクスチャを取得する
	/// </summary>
	/// <returns> 未設定テクスチャの場合に割り当てられる黒色テクスチャ </returns>
	unsigned int GetUndefineTexID() { return mUndefineTexID; }

	/// <summary>
	/// スカイボックスをアクティブにする
	/// </summary>
	/// <param name="_activeSkyBox"> キューブマップのポインタ </param>
	void SetActiveSkyBox(CubeMapComponent* _activeSkyBox) { mActiveSkyBox = _activeSkyBox; }

	/// <summary>
	/// キューブマップの頂点配列を取得する
	/// </summary>
	/// <returns> キューブマップの頂点配列 </returns>
	VertexArray* GetCubeMapVerts() { return mCubeVerts; }
};