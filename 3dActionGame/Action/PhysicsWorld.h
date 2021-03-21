//=============================================================================
//	@file	PhysicsWorld.h
//	@brief	当たり判定を行う
//=============================================================================

#pragma once

#include <vector>
#include <map>
#include <functional>
#include "Math.h"
#include "Collision.h"

#define PHYSICS PhysicsWorld::GetInstance()

class Game;
class GameObject;
class BoxCollider;
class SphereCollider;
class ColliderComponent;

typedef std::function<void(GameObject&)> onCollisionFunc;
typedef std::map<ColliderComponent*, std::function<void(GameObject&)>> onCollisionMap;

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

    std::vector<BoxCollider*> mBoxes;
	std::vector<BoxCollider*> mGroundBoxes;
	std::vector<BoxCollider*> mGlassBoxes;
	std::vector<BoxCollider*> mBlockBoxes;
	std::vector<BoxCollider*> mVerticalMoveGroundBoxes;
	std::vector<BoxCollider*> mJumpBoxes;
	std::vector<BoxCollider*> mLateralMoveGroundBoxes;
	std::vector<BoxCollider*> mPlayerBoxes;
	std::vector<BoxCollider*> mUpBlockBoxes;
	std::vector<BoxCollider*> mUpBlock_02Boxes;
	std::vector<BoxCollider*> mVerticalBlockBoxes;
	std::vector<BoxCollider*> mAerialBlockBoxes;
	std::vector<BoxCollider*> mRightBlockBoxes;
	std::vector<BoxCollider*> mLeftBlockBoxes;
	std::vector<BoxCollider*> mRightOneBlockBoxes;
	std::vector<BoxCollider*> mRightOneBlock_02Boxes;
	std::vector<BoxCollider*> mLeftOneBlockBoxes;
	std::vector<BoxCollider*> mLeftOneBlock_02Boxes;
	std::vector<BoxCollider*> mDownBlockBoxes;
	std::vector<BoxCollider*> mGoalBlockBoxes;
	std::vector<BoxCollider*> mRespawn01Boxes;
	std::vector<BoxCollider*> mRespawn02Boxes;
	std::vector<BoxCollider*> mRespawn03Boxes;
	std::vector<SphereCollider*> mSpheres;
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
