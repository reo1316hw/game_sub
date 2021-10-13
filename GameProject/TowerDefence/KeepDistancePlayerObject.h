#pragma once

/// <summary>
/// プレイヤーとの距離を保つ
/// </summary>
class KeepDistancePlayerObject : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> 親クラスのポインタ </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	/// <param name="_SceneTag"> シーンのタグ</param>
	KeepDistancePlayerObject(GameObject* _owner, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~KeepDistancePlayerObject() {};

	/// <summary>
	/// オブジェクトの更新処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	/// <summary>
	/// ヒットした時の処理
	/// </summary>
	/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
	void OnCollision(const GameObject& _HitObject)override;

	// 球状当たり判定
	Sphere mSphere;

	// ゲームオブジェクトのポインタ
	GameObject* mOwner;
	//// 球状当たり判定を行うクラスのポインタ
	//SphereCollider* mSphereColliderPtr;
};

