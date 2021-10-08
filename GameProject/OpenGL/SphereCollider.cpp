/// <summary>
/// 球の当たり判定を行うコンポーネント
/// </summary>

#include "pch.h"

/**
@brief	コンストラクタ
@param	アタッチするゲームオブジェクトのポインタ
@param	他のオブジェクトと当たった時に呼ばれる関数ポインタ(GetOnCollisionFuncを呼ぶ)
@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
@param	当たり判定時に、めり込みから動かす処理の優先度を決める数値
*/
SphereCollider::SphereCollider(GameObject* _owner, ColliderTag _tag, onCollisionFunc _func, int _updateOrder, int _collisionOrder)
	: ColliderComponent(_owner,_tag, _updateOrder, _collisionOrder)
	, mObjectSphere( Vector3::Zero,0.0f )
	, mWorldSphere( Vector3::Zero,0.0f )
{
	PHYSICS->AddSphere(this, _func);
}

/**
@brief	デストラクタ
*/
SphereCollider::~SphereCollider()
{
	PHYSICS->RemoveSphere(this);
}

/**
@brief	Transformのワールド変換
*/
void SphereCollider::OnUpdateWorldTransform()
{
	refresh();
	PHYSICS->HitCheck(this);
}

void SphereCollider::refresh()
{
	//ワールド座標での中心位置を更新する
	mWorldSphere.m_center = mObjectSphere.m_center + mOwner->GetPosition();
	//ワールド空間での球の大きさを更新する
	mWorldSphere.m_radius = mObjectSphere.m_radius * mOwner->GetScale();
}