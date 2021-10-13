#pragma once
#define PHYSICS PhysicsWorld::GetInstance()

// 前方宣言
class Game;
class GameObject;
class BoxCollider;
class SphereCollider;
class ColliderComponent;
class Shader;

typedef std::function<void(GameObject&)> onCollisionFunc;
typedef std::map<ColliderComponent*, std::function<void(GameObject&)>> onCollisionMap;

/// <summary>
/// 当たり判定を行う
/// </summary>
class PhysicsWorld
{
public:

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PhysicsWorld();

	/// <summary>
	/// インスタンスを作成する
	/// </summary>
	static void CreateInstance();

	/// <summary>
    /// インスタンスを削除する
    /// </summary>
	static void DeleteInstance();

    /// <summary>
    /// 矩形の当たり判定
	/// 矩形の当たり判定がどのオブジェクトと当たったかタグで調べる
    /// </summary>
    /// <param name="_box"> BoxColliderクラスのポインタ </param>
    void HitCheck(BoxCollider* _box);

    /// <summary>
    /// 球の当たり判定
    /// 球の当たり判定がどのオブジェクトと当たったかタグで調べる
	/// </summary>
    /// <param name="_sphere"> SphereColliderクラスのポインタ </param>
    void HitCheck(SphereCollider* _sphere);

    /// <summary>
    /// 矩形の当たり判定を追加
    /// </summary>
    /// <param name="_box"> 追加するBoxColliderクラスのポインタ </param>
    /// <param name="_func"> OnCollision関数のポインタ </param>
    void AddBox(BoxCollider* _box, onCollisionFunc _func);

    /// <summary>
    /// 矩形の当たり判定を削除
    /// </summary>
    /// <param name="_box"> 削除するBoxColliderクラスのポインタ </param>
    void RemoveBox(BoxCollider* _box);

	/// <summary>
	/// 球の当たり判定を追加
	/// </summary>
	/// <param name="_sphere"> 追加するSphereColliderクラスのポインタ </param>
	/// <param name="_func"> OnCollision関数のポインタ </param>
	void AddSphere(SphereCollider* _sphere, onCollisionFunc _func);

	/// <summary>
	/// 球の当たり判定を削除
	/// </summary>
	/// <param name="_sphere"> 削除するSphereColliderクラスのポインタ </param>
	void RemoveSphere(SphereCollider* _sphere);

	/// <summary>
	/// デバッグ用ボックス表示準備
	/// </summary>
	void DebugShowBox();

	/// <summary>
	/// デバッグモードフラグを切り替え
	/// </summary>
	void ToggleDebugMode() { mBoolDebugMode = !mBoolDebugMode; }

private:

	/// <summary>
	/// コンストラクタ
	/// 隠蔽
	/// </summary>
	PhysicsWorld();

	/// <summary>
	/// デバッグ用の矩形当たり判定を描画
	/// </summary>
	/// <param name="_Boxs"> 矩形当たり判定 </param>
	/// <param name="_Color"> ラインの色 </param>
	void DrawBoxs(std::vector<class BoxCollider*>& _Boxs, const Vector3& _Color);

	/// <summary>
	/// 頂点配列を初期化
	/// </summary>
	void InitBoxVertices();

	// 自分のインスタンス
	static PhysicsWorld* mPhysics;

	// ボックス描画用のVAO 
	unsigned int mBoxVAO; 

	// デバッグモードフラグ
	bool mBoolDebugMode;

	// 床の矩形当たり判定
	std::vector<BoxCollider*> mGroundBoxes;
	// 壁の矩形当たり判定
	std::vector<BoxCollider*> mWallBoxes;
	// プレイヤーの矩形当たり判定
	std::vector<BoxCollider*> mPlayerBoxes;
	// エネミーの矩形当たり判定
	std::vector<BoxCollider*> mEnemyBoxes;
	// 武器の矩形当たり判定
	std::vector<BoxCollider*> mWeaponBoxes;
	// プレイヤーの距離を保つための矩形当たり判定
	std::vector<BoxCollider*> mKeepDistancePlayerBoxes;

	//// プレイヤーの距離を保つための球状当たり判定
	//std::vector<SphereCollider*> mKeepDistancePlayerSpheres;

	// デバッグ用の当たり判定描画用シェーダー
	Shader* mLineShader;

	onCollisionMap mCollisionFunction;

public:// ゲッターセッター

	/// <summary>
	/// PhysicsWorldクラスのインスタンスを取得
	/// </summary>
	/// <returns> PhysicsWorldクラスのインスタンス(PhysicsWorld型) </returns>
	static PhysicsWorld* GetInstance() { return mPhysics; }
};

/// <summary>
/// 衝突したことが確定したとき、めり込みを戻す関数
/// </summary>
/// <param name="_MovableBox"> 移動物体 </param>
/// <param name="_FixedBox"> 移動しない物体 </param>
/// <param name="_calcFixVec"> 移動物体の補正差分ベクトル </param>
void CalcCollisionFixVec(const AABB& _MovableBox, const AABB& _FixedBox, Vector3& _calcFixVec);
