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
/// <param name="_UpdateOrder"> 更新処理の優先度 </param>
/// <param name="_CollisionOrder"> 当たり判定処理の優先度 </param>
BoxCollider::BoxCollider(GameObject* _owner, const Tag& _ObjectTag, const onCollisionFunc _Func, const int _UpdateOrder, const int _CollisionOrder)
	: ColliderComponent(_owner, _ObjectTag, _UpdateOrder, _CollisionOrder)
	, mIsIgnoreOwener(false)
	, mShouldRotate(true)
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
	// 基底クラスのGameObjectからでなく強制位置モードならOnWorldTransformを無視する
	if (mIsIgnoreOwener)
	{
		return;
	}

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

/// <summary>
/// 矩形当たり判定の行列変換を行う
/// </summary>
/// <param name="transform"> アタッチされたオブジェクトのワールド行列 </param>
void BoxCollider::SetForceTransForm(Matrix4 transform)
{
	mIsIgnoreOwener = true;
	// オブジェクト空間のボックスにリセット
	mWorldBox = mObjectBox;

	// スケーリング
	mWorldBox.m_min = (mObjectBox.m_min * mOwner->GetScale());
	mWorldBox.m_max = (mObjectBox.m_max * mOwner->GetScale());

	// 回転
	if (mShouldRotate)
	{
		mWorldBox.Rotate(Quaternion::MatrixToQuaternion(transform));
	}

	mWorldBox.m_min = Vector3::Transform(mWorldBox.m_min, transform);
	mWorldBox.m_max = Vector3::Transform(mWorldBox.m_max, transform);

}
