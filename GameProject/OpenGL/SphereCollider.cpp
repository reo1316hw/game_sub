/// <summary>
/// 球の当たり判定を行うコンポーネント
/// </summary>

#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> 親クラスのポインタ </param>
/// <param name="_ColliderTag"> 当たり判定のタグ </param>
/// <param name="_Func"> OnCollision関数のポインタ </param>
/// <param name="_UpdateOrder"> 更新処理の優先度 </param>
/// <param name="_CollisionOrder"> 当たり判定処理の優先度 </param>
SphereCollider::SphereCollider(GameObject* _owner, const ColliderTag _ColliderTag, const onCollisionFunc _Func, const int _UpdateOrder, const int _CollisionOrder)
	: ColliderComponent(_owner, _ColliderTag, _UpdateOrder, _CollisionOrder)
	, mObjectSphere( Vector3::Zero,0.0f )
	, mWorldSphere( Vector3::Zero,0.0f )
{
	PHYSICS->AddSphere(this, _Func);
}

/// <summary>
/// デストラクタ
/// </summary>
SphereCollider::~SphereCollider()
{
	PHYSICS->RemoveSphere(this);
}

/// <summary>
/// Transformのワールド変換
/// </summary>
void SphereCollider::OnUpdateWorldTransform()
{
	Refresh();
	PHYSICS->HitCheck(this);
}

/// <summary>
/// 押し戻し処理が行われたら行列変換を行う
/// </summary>
void SphereCollider::Refresh()
{
	//ワールド座標での中心位置を更新する
	mWorldSphere.m_center = mObjectSphere.m_center + mOwner->GetPosition();
	//ワールド空間での球の大きさを更新する
	mWorldSphere.m_radius = mObjectSphere.m_radius * mOwner->GetScale();
}