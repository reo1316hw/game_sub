#pragma once

/// <summary>
/// ボックスの当たり判定を行うコンポーネント
/// </summary>
class BoxCollider final : public ColliderComponent
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> 親クラスのポインタ </param>
	/// <param name="_ColliderTag"> 当たり判定のタグ </param>
	/// <param name="_Func"> OnCollision関数のポインタ </param>
	/// <param name="_UpdateOrder"> 更新処理の優先度 </param>
	/// <param name="_CollisionOrder"> 当たり判定処理の優先度 </param>
	BoxCollider(GameObject* _owner, const ColliderTag _ColliderTag, const onCollisionFunc _Func, const int _UpdateOrder = 200, const int _CollisionOrder = 100);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BoxCollider();

	/// <summary>
	/// Transformのワールド変換
	/// </summary>
	void OnUpdateWorldTransform() override;

	/// <summary>
	/// 押し戻し処理が行われたら行列変換を行う
	/// </summary>
	void Refresh();

private:

	// オーナーの移動処理を無視するか
	bool mIsIgnoreOwener;
	// 回転させるか
	bool mShouldRotate;

	// オブジェクトに設定する用のボックス（中心をオブジェクトの中心にする）
	AABB mObjectBox;
	// 当たり判定するときに使うボックス（中心をワールド座標の中心にする）
	AABB mWorldBox;

public:// ゲッターセッター

	/// <summary>
	/// 当たり判定に使うAABBの設定
	/// </summary>
	/// <param name="_box"> オブジェクトの大きさに合わせたAABBの構造体 </param>
	void SetObjectBox(const AABB& _box) { mObjectBox = _box; }

	/// <summary>
	/// 当たり判定時に使うワールド空間でのAABBを取得する
	/// </summary>
	/// <returns> 中心をワールド座標に合わせたAABBの構造体 </returns>
	AABB GetWorldBox() const { return mWorldBox; }
	
	/// <summary>
	/// 矩形当たり判定の行列変換を行う
	/// </summary>
	/// <param name="transform"> アタッチされたオブジェクトのワールド行列 </param>
	void  SetForceTransForm(Matrix4 transform);
};

