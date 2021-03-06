//=============================================================================
//	@file	BoxCollider.h
//	@brief	ボックスの当たり判定を行うコンポーネント
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	プリプロセッサ
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PhysicsWorld.h"
#include "ColliderComponent.h"

//-----------------------------------------------------------------------------
//	@brief	BoxColliderクラス
//-----------------------------------------------------------------------------
class BoxCollider final : public ColliderComponent
{
public:
//===================== publicのメンバ関数 ======================//

	/**
	@brief	コンストラクタ
	@param	アタッチするゲームオブジェクトのポインタ
	@param	他のオブジェクトと当たった時に呼ばれる関数ポインタ(GetOnCollisionFuncを呼ぶ)
	@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
	@param	当たり判定時に、めり込みから動かす処理の優先度を決める数値
	*/
	BoxCollider(GameObject* _owner, ColliderTag _tag,onCollisionFunc _func, int _updateOrder = 200, int _collisionOrder = 100);
	
	/**
	@brief	デストラクタ
	*/
	virtual ~BoxCollider();

	/**
	@brief	Transformのワールド変換
	*/
	void OnUpdateWorldTransform() override;
	void refresh();
	/**
	@brief	当たり判定に使うAABBの設定
	@param	オブジェクトの大きさに合わせたAABBの構造体
	*/
	void SetObjectBox(const AABB& _box) { mObjectBox = _box; }

	/**
	@brief	当たり判定時に使うワールド空間でのAABBを取得する
	@return 中心をワールド座標に合わせたAABBの構造体
	*/
	AABB GetWorldBox() const { return mWorldBox; }

private:
//===================== privateのメンバ変数 ======================//

	AABB mObjectBox;			//オブジェクトに設定する用のボックス（中心をオブジェクトの中心にする）
	AABB mWorldBox;			//当たり判定するときに使うボックス（中心をワールド座標の中心にする）
	bool mShouldRotate;
};

