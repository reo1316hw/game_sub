//=============================================================================
//	@file	PhysicsWorld.cpp
//	@brief	当たり判定を行う
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#include "PhysicsWorld.h"
#include <algorithm>
#include <SDL.h>
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "ColliderComponent.h"

PhysicsWorld* PhysicsWorld::physics = nullptr;

PhysicsWorld::PhysicsWorld()
{
}

void PhysicsWorld::CreateInstance()
{
	if (physics == nullptr)
	{
		physics = new PhysicsWorld();
	}
}

void PhysicsWorld::DeleteInstance()
{
	if (physics != nullptr)
	{
		delete physics;
		physics = nullptr;
	}
}

void PhysicsWorld::HitCheck()
{
	SphereAndSphere();
    BoxAndBox();
    SphereAndBox();
}

void PhysicsWorld::HitCheck(BoxCollider* _box)
{
	//コライダーの親オブジェクトがActiveじゃなければ終了する
	if (_box->GetOwner()->GetState() != State::Active)
	{
		return;
	}

	if (_box->GetTag() == ColliderTag::Player)
	{
		for (auto itr : groundBoxes)
		{
			if (itr == _box)
			{
				continue;
			}
			//コライダーの親オブジェクトがActiveじゃなければ終了する 
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_box);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_box->GetOwner()));
				_box->refresh();
			}
		}
		for (auto itr : wallBoxes)
		{
			if (itr == _box)
			{
				continue;
			}
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_box);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_box->GetOwner()));
				_box->refresh();
			}
		}

		for (auto itr : enemyBoxes)
		{
			if (itr == _box)
			{
				continue;
			}
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
			if (hit)
			{
				onCollisionFunc func = collisionFunction.at(_box);
				func(*(itr->GetOwner()));
				func = collisionFunction.at(itr);
				func(*(_box->GetOwner()));
				_box->refresh();
			}
		}
	}
}

void PhysicsWorld::HitCheck(SphereCollider * _sphere)
{
	//コライダーの親オブジェクトがActiveじゃなければ終了する
	if (_sphere->GetOwner()->GetState() != State::Active)
	{
		return;
	}

	//if (_sphere->GetTag() == ColliderTag::isGround)
	//{
	//	for (auto itr : groundBoxes)
	//	{
	//		//コライダーの親オブジェクトがActiveじゃなければ終了する 
	//		if (itr->GetOwner()->GetState() != State::Active)
	//		{
	//			continue;
	//		}
	//		bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_sphere);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_sphere->GetOwner()));
	//			_sphere->refresh();
	//		}
	//	}
	//	for (auto itr : wallBoxes)
	//	{
	//		//コライダーの親オブジェクトがActiveじゃなければ終了する
	//		if (itr->GetOwner()->GetState() != State::Active)
	//		{
	//			continue;
	//		}
	//		bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = collisionFunction.at(_sphere);
	//			func(*(itr->GetOwner()));
	//			func = collisionFunction.at(itr);
	//			func(*(_sphere->GetOwner()));
	//			_sphere->refresh();
	//		}
	//	}
	//}
}

void PhysicsWorld::AddBox(BoxCollider * _box, onCollisionFunc _func)
{
	if (_box->GetTag() == ColliderTag::Ground)
	{
		groundBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::Wall)
	{
		wallBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::Player)
	{
		playerBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::Enemy)
	{
		enemyBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
}

void PhysicsWorld::RemoveBox(BoxCollider * _box)
{

	auto groundBox = std::find(groundBoxes.begin(), groundBoxes.end(), _box);
	if (groundBox != groundBoxes.end())
	{
		std::iter_swap(groundBox, groundBoxes.end() - 1);
		groundBoxes.pop_back();
	}
	auto wallBox = std::find(wallBoxes.begin(), wallBoxes.end(), _box);
	if (wallBox != wallBoxes.end())
	{
		std::iter_swap(wallBox, wallBoxes.end() - 1);
		wallBoxes.pop_back();
	}
	auto playerBox = std::find(playerBoxes.begin(), playerBoxes.end(), _box);
	if (playerBox != playerBoxes.end())
	{
		std::iter_swap(playerBox, playerBoxes.end() - 1);
		playerBoxes.pop_back();
	}

	auto enemyBox = std::find(enemyBoxes.begin(), enemyBoxes.end(), _box);
	if (enemyBox != enemyBoxes.end())
	{
		std::iter_swap(enemyBox, enemyBoxes.end() - 1);
		enemyBoxes.pop_back();
	}

    collisionFunction.erase(_box);
}

void PhysicsWorld::AddSphere(SphereCollider * _sphere, onCollisionFunc _func)
{
	playerSpheres.emplace_back(_sphere);
    //コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
    collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_sphere), _func));
}

void PhysicsWorld::RemoveSphere(SphereCollider * _sphere)
{
	auto iter = std::find(playerSpheres.begin(), playerSpheres.end(), _sphere);
	if (iter != playerSpheres.end())
	{
		std::iter_swap(iter, playerSpheres.end() - 1);
		playerSpheres.pop_back();
	}
    collisionFunction.erase(_sphere);
}

void PhysicsWorld::SphereAndSphere()
{
	//for (size_t i = 0; i < spheres.size(); i++)
	//{
	//	if (spheres[i]->GetOwner()->GetState() != Active)
	//	{
	//		continue;
	//	}
	//	for (size_t j = i + 1; j < spheres.size(); j++)
	//	{
	//		if (spheres[j]->GetOwner()->GetState() != Active)
	//		{
	//			continue;
	//		}
	//		bool hit = Intersect(spheres[i]->GetWorldSphere(), spheres[j]->GetWorldSphere());

	//		if (hit)
	//		{
	//			SphereCollider* sphereA = spheres[i];
	//			SphereCollider* sphereB = spheres[j];

	//			//sphereA->GetOwner()->OnCollision(*(sphereB->GetOwner()));
	//			//sphereB->GetOwner()->OnCollision(*(sphereA->GetOwner()));
	//		}
	//	}
	//}
}

void PhysicsWorld::BoxAndBox()
{
	//for (size_t i = 0; i < boxes.size(); i++)
	//{
	//	if (boxes[i]->GetOwner()->GetState() != Active)
	//	{
	//		continue;
	//	}
	//	for (size_t j = i + 1; j < boxes.size(); j++)
	//	{
	//		if (boxes[j]->GetOwner()->GetState() != Active)
	//		{
	//			continue;
	//		}
	//		bool hit = Intersect(boxes[i]->GetWorldBox(), boxes[j]->GetWorldBox());

	//		if (hit)
	//		{
	//			BoxCollider* boxA = boxes[i];
	//			BoxCollider* boxB = boxes[j];

	//			//boxA->GetOwner()->OnCollision(*(boxB->GetOwner()));
	//			//boxB->GetOwner()->OnCollision(*(boxA->GetOwner()));
	//		}
	//	}
	//}
}

void PhysicsWorld::SphereAndBox()
{
	//for (size_t i = 0; i < spheres.size(); i++)
	//{
	//	if (spheres[i]->GetOwner()->GetState() != Active)
	//	{
	//		continue;
	//	}
	//	for (size_t j = 0; j < boxes.size(); j++)
	//	{
	//		if (boxes[j]->GetOwner()->GetState() != Active)
	//		{
	//			continue;
	//		}
	//		bool hit = Intersect(spheres[i]->GetWorldSphere(), boxes[j]->GetWorldBox());

	//		if (hit)
	//		{
	//			//spheres[i]->GetOwner()->OnCollision(*(boxes[j]->GetOwner()));
	//			//boxes[j]->GetOwner()->OnCollision(*(spheres[i]->GetOwner()));
	//		}
	//	}
	//}
}

/*
@fn 衝突したことが確定したとき、めり込みを戻す関数
@param _movableBox 移動物体
@param _fixedBox 移動しない物体
@param _calcFixVec 移動物体の補正差分ベクトル
*/
void calcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec)
{
	_calcFixVec = Vector3(0, 0, 0);
	float dx1 = _fixedBox.min.x - _movableBox.max.x;
	float dx2 = _fixedBox.max.x - _movableBox.min.x;
	float dy1 = _fixedBox.min.y - _movableBox.max.y;
	float dy2 = _fixedBox.max.y - _movableBox.min.y;
	float dz1 = _fixedBox.min.z - _movableBox.max.z;
	float dz2 = _fixedBox.max.z - _movableBox.min.z;

	// dx, dy, dz には それぞれ1,2のうち絶対値が小さい方をセットする
	float dx = (Math::Abs(dx1) < Math::Abs(dx2)) ? dx1 : dx2;
	float dy = (Math::Abs(dy1) < Math::Abs(dy2)) ? dy1 : dy2;
	float dz = (Math::Abs(dz1) < Math::Abs(dz2)) ? dz1 : dz2;

	// x, y, zのうち最も差が小さい軸で位置を調整
	if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
	{
		_calcFixVec.x = dx;
	}
	else if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
	{
		_calcFixVec.y = dy;
	}
	else
	{
		_calcFixVec.z = dz;
	}

}
