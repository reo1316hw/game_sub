/// <summary>
/// ボックスの当たり判定を行うコンポーネント
/// </summary>

#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> 親クラスのポインタ </param>
/// <param name="_ObjectTag"> 当たり判定のタグ </param>
/// <param name="_Func"> OnCollision関数のポインタ </param>
/// <param name="_IsRotate"> 回転させるか </param>
/// <param name="_UpdateOrder"> 更新処理の優先度 </param>
/// <param name="_CollisionOrder"> 当たり判定処理の優先度 </param>
BoxCollider::BoxCollider(GameObject* _owner, const Tag& _ObjectTag, const onCollisionFunc _Func, const bool& _IsRotate, const int& _UpdateOrder, const int& _CollisionOrder)
	: ColliderComponent(_owner, _ObjectTag, _UpdateOrder, _CollisionOrder)
	, mShouldRotate(_IsRotate)
	, mObjectBox(Vector3::Zero,Vector3::Zero)
	, mWorldBox(Vector3::Zero,Vector3::Zero)
{
	PHYSICS->AddBox(this, _Func);
}

/// <summary>
/// デストラクタ
/// </summary>
BoxCollider::~BoxCollider()
{
	PHYSICS->RemoveBox(this);
}

/// <summary>
/// Transformのワールド変換
/// </summary>
void BoxCollider::OnUpdateWorldTransform()
{
	Refresh();
	PHYSICS->HitCheck(this);
}

/// <summary>
/// 押し戻し処理が行われたら行列変換を行う
/// </summary>
void BoxCollider::Refresh()
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