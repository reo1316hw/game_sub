#pragma once
#define PHYSICS PhysicsWorld::GetInstance()

// 前方宣言
class Game;
class GameObject;
class BoxCollider;
class SphereCollider;
class ColliderComponent;

typedef std::function<void(GameObject&)> onCollisionFunc;
typedef std::map<ColliderComponent*, std::function<void(GameObject&)>> onCollisionMap;

/// <summary>
/// 当たり判定を行う
/// </summary>
class PhysicsWorld
{
public:

	static PhysicsWorld* GetInstance() { return mPhysics; }
	static void CreateInstance();
	static void DeleteInstance();

	//当たり判定
    void HitCheck();
    void HitCheck(BoxCollider* _box);
    void HitCheck(SphereCollider* _sphere);

    void AddBox(BoxCollider* _box, onCollisionFunc _func);
    void RemoveBox(BoxCollider* _box);
	void AddSphere(SphereCollider* _sphere, onCollisionFunc _func);
	void RemoveSphere(SphereCollider* _sphere);


	void SphereAndBox();


private:

	//コンストラクタの隠蔽
	PhysicsWorld();

	static PhysicsWorld* mPhysics;

	void SphereAndSphere();
	void BoxAndBox();

    //std::vector<BoxCollider*> boxes;
	//std::vector<SphereCollider*> spheres;

	std::vector<BoxCollider*> mGroundBoxes;
	std::vector<BoxCollider*> mWallBoxes;
	std::vector<BoxCollider*> mPlayerBoxes;
	std::vector<BoxCollider*> mEnemyBoxes;

	std::vector<SphereCollider*> mPlayerSpheres;

	onCollisionMap mCollisionFunction;
};

/*
@fn 衝突したことが確定したとき、めり込みを戻す関数
@param _movableBox 移動物体
@param _fixedBox 移動しない物体
@param _calcFixVec 移動物体の補正差分ベクトル
*/
void calcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);
