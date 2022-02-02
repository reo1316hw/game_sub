#pragma once

/// <summary>
/// 球の当たり判定を行うコンポーネント
/// </summary>
class SphereCollider final : public ColliderComponent
{
public:

	/// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="_owner"> 親クラスのポインタ </param>
    /// <param name="_ObjectTag"> 当たり判定のタグ </param>
    /// <param name="_Func"> OnCollision関数のポインタ </param>
    /// <param name="_UpdateOrder"> 更新処理の優先度 </param>
    /// <param name="_CollisionOrder"> 当たり判定処理の優先度 </param>
	SphereCollider(GameObject* _owner, const Tag& _ObjectTag, const onCollisionFunc _Func, const int _UpdateOrder = 200, const int _CollisionOrder = 100);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~SphereCollider();

	/// <summary>
	/// Transformのワールド変換
	/// </summary>
	void OnUpdateWorldTransform() override;

	/// <summary>
    /// 押し戻し処理が行われたら行列変換を行う
    /// </summary>
	void Refresh();

private:

	//オブジェクトに設定する用の球（中心をオブジェクトの中心にする）
	Sphere mObjectSphere;
	//当たり判定するときに使う球（中心をワールド座標の中心にする）
	Sphere mWorldSphere;

public:

	/// <summary>
	/// 当たり判定に使うSphereの設定
	/// </summary>
	/// <param name="_sphere"> オブジェクトの大きさに合わせたSphereの構造体 </param>
	void SetObjectSphere(const Sphere& _sphere) { mObjectSphere = _sphere; }

	/// <summary>
	/// 当たり判定時に使うワールド空間でのSphereを取得する
	/// </summary>
	/// <returns> 中心をワールド座標に合わせたSphereの構造体 </returns>
	Sphere GetWorldSphere() const { return mWorldSphere; }
};

