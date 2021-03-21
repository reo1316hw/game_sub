﻿//=============================================================================
//	@file	BoxCollider.h
//	@brief	ボックスの当たり判定を行うコンポーネント
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "BoxCollider.h"
#include "Math.h"
#include "GameObject.h"
#include "Collision.h"
#include "Game.h"

/**
@brief	コンストラクタ
@param	アタッチするゲームオブジェクトのポインタ
@param	他のオブジェクトと当たった時に呼ばれる関数ポインタ(GetOnCollisionFuncを呼ぶ)
@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
@param	当たり判定時に、めり込みから動かす処理の優先度を決める数値
*/
BoxCollider::BoxCollider(GameObject* _owner, ColliderTag _tag,onCollisionFunc _func, int _updateOrder, int _collisionOrder)
	: ColliderComponent(_owner,_tag, _updateOrder, _collisionOrder)
	, objectBox({Vector3::Zero,Vector3::Zero})
	, worldBox({ Vector3::Zero,Vector3::Zero})
	, shouldRotate(true)
{
	PHYSICS->AddBox(this,_func);
}

/**
@brief	デストラクタ
*/
BoxCollider::~BoxCollider()
{
	PHYSICS->RemoveBox(this);
}

/**
@brief	Transformのワールド変換
*/
void BoxCollider::OnUpdateWorldTransform()
{
	refresh();
	PHYSICS->HitCheck(this);
}

void BoxCollider::refresh()
{
	worldBox = objectBox;

	worldBox.min = (objectBox.min * mOwner->GetScaleVec());
	worldBox.max = (objectBox.max * mOwner->GetScaleVec());

	if (shouldRotate)
	{
		worldBox.Rotate(mOwner->GetRotation());
	}

	worldBox.min += mOwner->GetPosition();
	worldBox.max += mOwner->GetPosition();
}

