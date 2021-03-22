//=============================================================================
//	@file	BoxCollider.h
//	@brief	ボックスの当たり判定を行うコンポーネント
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
	, mObjectBox(Vector3::Zero,Vector3::Zero)
	, mWorldBox(Vector3::Zero,Vector3::Zero)
	, mShouldRotate(true)
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
	mWorldBox = mObjectBox;

	mWorldBox.m_min = (mObjectBox.m_min * mOwner->GetScale());
	mWorldBox.m_max = (mObjectBox.m_max * mOwner->GetScale());

	if (mShouldRotate)
	{
		mWorldBox.Rotate(mOwner->GetRotation());
	}

	mWorldBox.m_min += mOwner->GetPosition();
	mWorldBox.m_max += mOwner->GetPosition();
}

