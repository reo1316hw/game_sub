/// <summary>
/// ボックスの当たり判定を行うコンポーネント
/// </summary>

#include "pch.h"

/**
@brief	コンストラクタ
@param	アタッチするゲームオブジェクトのポインタ
@param	他のオブジェクトと当たった時に呼ばれる関数ポインタ(GetOnCollisionFuncを呼ぶ)
@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
@param	当たり判定時に、めり込みから動かす処理の優先度を決める数値
*/

BoxCollider::BoxCollider(GameObject* _owner, ColliderTag _tag,onCollisionFunc _func, int _updateOrder, int _collisionOrder)
	: ColliderComponent(_owner,_tag, _updateOrder, _collisionOrder)
	, mIsIgnoreOwener(false)
	, mShouldRotate(true)
	, mObjectBox(Vector3::Zero,Vector3::Zero)
	, mWorldBox(Vector3::Zero,Vector3::Zero)
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

// 強制的にボックスに対し変換行列
void BoxCollider::SetForceTransForm(Matrix4 transform)
{
	mIsIgnoreOwener = true;
	// オブジェクト空間のボックスにリセット
	mWorldBox = mObjectBox;

	// スケーリング
	mWorldBox.m_min = (mObjectBox.m_min * mOwner->GetScale());
	mWorldBox.m_max = (mObjectBox.m_max * mOwner->GetScale());

	mWorldBox.m_min = Vector3::Transform(mWorldBox.m_min, transform);
	mWorldBox.m_max = Vector3::Transform(mWorldBox.m_max, transform);

}
