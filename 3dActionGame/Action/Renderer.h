#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "Math.h"
#include "ParticleComponent.h"
#include "PlayerObject.h"

#define RENDERER Renderer::GetInstance()

//平行光源用の構造体
struct DirectionalLight
{
	// 光の方向
	Vector3 direction;
	// 拡散反射色
	Vector3 diffuseColor;
	// 鏡面反射色
	Vector3 specColor;
};

enum class TextureStage
{
	DiffuseMap,
	NormalMap,
	SpecularMap,
	EmissiveMap,
	ShadowMap,
};

class SpriteComponent;
class Texture;
class Mesh;
class Game;
class MeshComponent;
class InvisibleMeshComponent;
class Shader;
class VertexArray;
class ParticleComponent;
class UIComponent;
class HeartUI;
class HDRRenderer;

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
	static Renderer* GetInstance() { return renderer; }

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
	@brief  UIの追加
	@param	_ui　追加するUIクラスのポインタ
	*/
	void AddUI(UIComponent* _ui);

	/*
	@brief UIの削除
	@param	_ui　削除するUIクラスのポインタ
	*/
	void RemoveUI(UIComponent* _ui);

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
	const class Skeleton* GetSkeleton(const char* fileName);                       
	/*
	@param _fileName アニメーションへのアドレス
	@return スケルトンアニメーションの取得
	*/
	const class Animation* GetAnimation(const char* fileName, bool _loop);                     // スケルタルアニメーションの取得

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
	void SetViewMatrix(const Matrix4& _view) { view = _view; }

	/*
	@brief	環境光を設定する
	@param	_ambient Vector3（環境光を表す）
	*/
	void SetAmbientLight(const Vector3& _ambient) { ambientLight = _ambient; }

	/*
	@brief	平行光源の構造体を取得する
	@return	DirectionalLight（平行光源の構造体）
	*/
	DirectionalLight& GetDirectionalLight() { return dirLight; }

	/*
	@brief	スクリーンの横幅を取得する
	@return	スクリーンの横幅
	*/
	float GetScreenWidth() const { return screenWidth; }

	/*
	@brief	スクリーンの縦幅を取得する
	@return	スクリーンの縦幅
	*/
	float GetScreenHeight() const { return screenHeight; }

	Matrix4 GetViewMatrix() const { return view; };

	void SetParticleVertex();

	Matrix4 GetProjectionMatrix() { return projection; }

	SDL_Renderer* GetSDLRenderer() { return sdlRenderer; }

	unsigned int GetUndefineTexID() { return mUndefineTexID; }

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
	static Renderer* renderer;
	SDL_Renderer* sdlRenderer;

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

	void Draw3DScene(unsigned int framebuffer, const Matrix4& view, const Matrix4& proj,
		float viewPortScale = 1.0f, bool lit = true);

	/*
	@brief  光源情報をシェーダーの変数にセットする
	@param  _shader セットするShaderクラスのポインタ
	*/
	void SetLightUniforms(Shader* _shader, const Matrix4& view);

	void ChangeBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM blendType);
	void ChangeTexture(int changeTextureID);

	Vector3 CalcCameraPos();

	//ファイル名でメッシュを取得するための連想配列
	std::unordered_map<std::string, Mesh*> meshes;
	//メッシュコンポーネントのポインタの可変長コンテナ
	std::vector<MeshComponent*> meshComponents;
	//インビジブルメッシュコンポーネントのポインタの可変長コンテナ
	std::vector<InvisibleMeshComponent*> invisibleMeshComponents;
	//スプライトコンポーネントのポインタの可変長コンテナ
	std::vector<SpriteComponent*> sprites;
	//UIのポインタの可変長コンテナ
	std::vector<UIComponent*> uis;
	//パーティクルのポインタ
	std::vector<ParticleComponent*> particles;
	//ファイル名でテクスチャを取得するための連想配列
	std::unordered_map<std::string, Texture*>textures;

	//クラスのポインタ
	//スプライト
	Shader* spriteShader;
	VertexArray* spriteVerts;
	//UI
	Shader* uiShader;
	VertexArray* uiVerts;
	//メッシュ
	Shader* meshShader;
	//スキンメッシュ
	class Shader*  mSkinnedShader;  
	//インビジブルメッシュ
	Shader* invisibleMeshShader;
	Shader* basicShader;
	//パーティクル
	Shader* particleShader;
	// パーティクル用頂点定義
	VertexArray* particleVertex;   
	// プレイヤー
	PlayerObject* player;

	// HDR レンダラー
	HDRRenderer* mHDRRenderer;

	//ビュー行列
	Matrix4 view;
	//射影行列
	Matrix4 projection;
	//ビルボード行列
	Matrix4 mBillboardMat;
	//スクリーンの横幅
	float screenWidth;
	//スクリーンの縦幅
	float screenHeight;
	//環境光
	Vector3 ambientLight;
	//平行光源
	DirectionalLight dirLight;
	//ウィンドウ
	SDL_Window* window;
	//コンテキスト
	SDL_GLContext context;
	// UIの初期座標に加算される座標
	Vector2 addPosition;

	HeartUI* heartUI;

	// 未設定テクスチャの場合に割り当てられる黒色テクスチャ
	unsigned int mUndefineTexID;
};