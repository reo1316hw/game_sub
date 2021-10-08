﻿/// <summary>
/// 当たり判定を行う
/// </summary>

#include "pch.h"

PhysicsWorld* PhysicsWorld::mPhysics = nullptr;

PhysicsWorld::PhysicsWorld()
	: mBoolDebugMode(false)
{
	InitBoxVertices();

	mLineShader = new Shader();
	mLineShader->Load("shaders/LineWorld.vert", "shaders/Line.frag");
}

// デストラクタ
PhysicsWorld::~PhysicsWorld()
{
	delete mLineShader;
}

void PhysicsWorld::CreateInstance()
{
	if (mPhysics == nullptr)
	{
		mPhysics = new PhysicsWorld();
	}
}

void PhysicsWorld::DeleteInstance()
{
	if (mPhysics != nullptr)
	{
		delete mPhysics;
		mPhysics = nullptr;
	}
}

void PhysicsWorld::DebugShowBox()
{
	// デバッグモードか？
	if (!mBoolDebugMode)
	{
		return;
	}

	// AABB描画準備
	Matrix4 scale, trans, world, view, proj, viewProj;
	view = RENDERER->GetViewMatrix();
	proj = RENDERER->GetProjectionMatrix();
	viewProj = view * proj;
	mLineShader->SetActive();
	mLineShader->SetMatrixUniform("uViewProj", viewProj);

	// 当たり判定ボックス描画
	DrawBoxs(mGroundBoxes, Color::Red);
	DrawBoxs(mWallBoxes, Color::Blue);
	DrawBoxs(mPlayerBoxes, Color::LightPink);
	DrawBoxs(mEnemyBoxes, Color::White);
	DrawBoxs(mWeaponBoxes, Color::LightGreen);
}

void PhysicsWorld::DrawBoxs(std::vector<class BoxCollider*>& boxs, const Vector3& color)
{
	Matrix4 scaleMat, posMat, worldMat;
	Vector3 scale, pos;

	mLineShader->SetVectorUniform("uColor", color);
	for (auto item : boxs)
	{
		AABB box = AABB(Vector3::Zero, Vector3::Zero);
		Vector3 min, max;
		box = item->GetWorldBox();

		// ボックスのスケールと位置を取得
		min = box.m_min;
		max = box.m_max;
		scale = max - min;
		pos = min;

		scaleMat = Matrix4::CreateScale(scale);
		posMat = Matrix4::CreateTranslation(pos);

		worldMat = scaleMat * posMat;
		mLineShader->SetMatrixUniform("uWorld", worldMat);

		glBindVertexArray(mBoxVAO);
		glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
	}

}

void PhysicsWorld::InitBoxVertices()
{
	// ボックス頂点リスト
	float vertices[] = {
		0.0f, 0.0f, 0.0f,  // min
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,  // max
		0.0f, 1.0f, 1.0f,
	};
	// ボックスのラインリスト
	unsigned int lineList[] = {
		0,1,
		1,2,
		2,3,
		3,0,
		4,5,
		5,6,
		6,7,
		7,4,
		0,4,
		1,5,
		2,6,
		3,7,
	};
	unsigned int vbo, ebo;
	glGenVertexArrays(1, &mBoxVAO);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindVertexArray(mBoxVAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lineList), lineList, GL_STATIC_DRAW);
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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
		//for (auto itr : mGroundBoxes)
		//{
		//	if (itr == _box)
		//	{
		//		continue;
		//	}
		//	//コライダーの親オブジェクトがActiveじゃなければ終了する 
		//	if (itr->GetOwner()->GetState() != State::Active)
		//	{
		//		continue;
		//	}
		//	bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
		//	if (hit)
		//	{
		//		onCollisionFunc func = mCollisionFunction.at(_box);
		//		func(*(itr->GetOwner()));
		//		func = mCollisionFunction.at(itr);
		//		func(*(_box->GetOwner()));
		//		_box->refresh();
		//	}
		//}
		//for (auto itr : mWallBoxes)
		//{
		//	if (itr == _box)
		//	{
		//		continue;
		//	}
		//	//コライダーの親オブジェクトがActiveじゃなければ終了する
		//	if (itr->GetOwner()->GetState() != State::Active)
		//	{
		//		continue;
		//	}
		//	bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
		//	if (hit)
		//	{
		//		onCollisionFunc func = mCollisionFunction.at(_box);
		//		func(*(itr->GetOwner()));
		//		func = mCollisionFunction.at(itr);
		//		func(*(_box->GetOwner()));
		//		_box->refresh();
		//	}
		//}

		for (auto itr : mEnemyBoxes)
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
				onCollisionFunc func = mCollisionFunction.at(_box);
				func(*(itr->GetOwner()));
				func = mCollisionFunction.at(itr);
				func(*(_box->GetOwner()));
				_box->refresh();
			}
		}
	}

	if (_box->GetTag() == ColliderTag::Enemy)
	{
		//for (auto itr : mGroundBoxes)
		//{
		//	if (itr == _box)
		//	{
		//		continue;
		//	}
		//	//コライダーの親オブジェクトがActiveじゃなければ終了する 
		//	if (itr->GetOwner()->GetState() != State::Active)
		//	{
		//		continue;
		//	}
		//	bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
		//	if (hit)
		//	{
		//		onCollisionFunc func = mCollisionFunction.at(_box);
		//		func(*(itr->GetOwner()));
		//		func = mCollisionFunction.at(itr);
		//		func(*(_box->GetOwner()));
		//		_box->refresh();
		//	}
		//}
		//for (auto itr : mWallBoxes)
		//{
		//	if (itr == _box)
		//	{
		//		continue;
		//	}
		//	//コライダーの親オブジェクトがActiveじゃなければ終了する
		//	if (itr->GetOwner()->GetState() != State::Active)
		//	{
		//		continue;
		//	}
		//	bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
		//	if (hit)
		//	{
		//		onCollisionFunc func = mCollisionFunction.at(_box);
		//		func(*(itr->GetOwner()));
		//		func = mCollisionFunction.at(itr);
		//		func(*(_box->GetOwner()));
		//		_box->refresh();
		//	}
		//}
		//for (auto itr : mEnemyBoxes)
		//{
		//	if (itr == _box)
		//	{
		//		continue;
		//	}
		//	//コライダーの親オブジェクトがActiveじゃなければ終了する
		//	if (itr->GetOwner()->GetState() != State::Active)
		//	{
		//		continue;
		//	}
		//	bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
		//	if (hit)
		//	{
		//		onCollisionFunc func = mCollisionFunction.at(_box);
		//		func(*(itr->GetOwner()));
		//		func = mCollisionFunction.at(itr);
		//		func(*(_box->GetOwner()));
		//		_box->refresh();
		//	}
		//}

		for (auto itr : mWeaponBoxes)
		{
			//コライダーの親オブジェクトがActiveじゃなければ終了する
			if (itr->GetOwner()->GetState() != State::Active)
			{
				continue;
			}
			bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
			if (hit)
			{
 				onCollisionFunc func = mCollisionFunction.at(_box);
				func(*(itr->GetOwner()));
				func = mCollisionFunction.at(itr);
				func(*(_box->GetOwner()));
				_box->refresh();
			}
		}
		for (auto itr : mPlayerBoxes)
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
				onCollisionFunc func = mCollisionFunction.at(_box);
				func(*(itr->GetOwner()));
				func = mCollisionFunction.at(itr);
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

	//if (_sphere->GetTag() == ColliderTag::Weapon)
	//{
	//	for (auto itr : mEnemyBoxes)
	//	{
	//		//コライダーの親オブジェクトがActiveじゃなければ終了する
	//		if (itr->GetOwner()->GetState() != State::Active)
	//		{
	//			continue;
	//		}
	//		bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());
	//		if (hit)
	//		{
	//			onCollisionFunc func = mCollisionFunction.at(_sphere);
	//			func(*(itr->GetOwner()));
	//			func = mCollisionFunction.at(itr);
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
		mGroundBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		mCollisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::Wall)
	{
		mWallBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		mCollisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::Player)
	{
		mPlayerBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		mCollisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::Enemy)
	{
		mEnemyBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		mCollisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	if (_box->GetTag() == ColliderTag::Weapon)
	{
		mWeaponBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		mCollisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
}

void PhysicsWorld::RemoveBox(BoxCollider * _box)
{

	auto groundBox = std::find(mGroundBoxes.begin(), mGroundBoxes.end(), _box);
	if (groundBox != mGroundBoxes.end())
	{
		std::iter_swap(groundBox, mGroundBoxes.end() - 1);
		mGroundBoxes.pop_back();
	}
	auto wallBox = std::find(mWallBoxes.begin(), mWallBoxes.end(), _box);
	if (wallBox != mWallBoxes.end())
	{
		std::iter_swap(wallBox, mWallBoxes.end() - 1);
		mWallBoxes.pop_back();
	}
	auto playerBox = std::find(mPlayerBoxes.begin(), mPlayerBoxes.end(), _box);
	if (playerBox != mPlayerBoxes.end())
	{
		std::iter_swap(playerBox, mPlayerBoxes.end() - 1);
		mPlayerBoxes.pop_back();
	}

	auto enemyBox = std::find(mEnemyBoxes.begin(), mEnemyBoxes.end(), _box);
	if (enemyBox != mEnemyBoxes.end())
	{
		std::iter_swap(enemyBox, mEnemyBoxes.end() - 1);
		mEnemyBoxes.pop_back();
	}

	auto weaponBox = std::find(mWeaponBoxes.begin(), mWeaponBoxes.end(), _box);
	if (weaponBox != mWeaponBoxes.end())
	{
		std::iter_swap(weaponBox, mWeaponBoxes.end() - 1);
		mWeaponBoxes.pop_back();
	}

    mCollisionFunction.erase(_box);
}

void PhysicsWorld::AddSphere(SphereCollider * _sphere, onCollisionFunc _func)
{
	//mWeaponSpheres.emplace_back(_sphere);
    //コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
    //mCollisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_sphere), _func));
}

void PhysicsWorld::RemoveSphere(SphereCollider * _sphere)
{
	/*auto iter = std::find(mWeaponSpheres.begin(), mWeaponSpheres.end(), _sphere);
	if (iter != mWeaponSpheres.end())
	{
		std::iter_swap(iter, mWeaponSpheres.end() - 1);
		mWeaponSpheres.pop_back();
	}
    mCollisionFunction.erase(_sphere);*/
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
	float dx1 = _fixedBox.m_min.x - _movableBox.m_max.x;
	float dx2 = _fixedBox.m_max.x - _movableBox.m_min.x;
	float dy1 = _fixedBox.m_min.y - _movableBox.m_max.y;
	float dy2 = _fixedBox.m_max.y - _movableBox.m_min.y;
	float dz1 = _fixedBox.m_min.z - _movableBox.m_max.z;
	float dz2 = _fixedBox.m_max.z - _movableBox.m_min.z;

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
