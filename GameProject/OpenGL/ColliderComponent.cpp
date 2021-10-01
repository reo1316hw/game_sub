//=============================================================================
//	@file	ColliderComponent.cpp
//	@brief	当たり判定を行うコンポーネントの規定クラス
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ColliderComponent.h"
#include "Game.h"
#include "PhysicsWorld.h"

/**
@brief	コンストラクタ
@param	アタッチするゲームオブジェクトのポインタ
@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
@param  当たり判定時に、めり込みから動かす処理の優先度を決める数値
*/
ColliderComponent::ColliderComponent(GameObject* _owner, ColliderTag _tag, int _updateOrder, int _collisionOrder)
	: Component(_owner, _updateOrder)
	, mTriggerFlag(false)
	, mCollisionOrder(_collisionOrder)
	, mTag(_tag)
{
}

