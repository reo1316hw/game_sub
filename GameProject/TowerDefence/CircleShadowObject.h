#pragma once

/// <summary>
/// 丸い影
/// </summary>
class CircleShadowObject : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> 親クラスのポインタ </param>
	/// <param name="_Scale"> 大きさ </param>
	/// <param name="_GpmeshName"> gpmeshのパス </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	CircleShadowObject(GameObject* _owner, const Vector3& _Scale, const std::string _GpmeshName, const Tag& _ObjectTag);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CircleShadowObject() {};

	/// <summary>
	/// オブジェクトの更新処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	// 親オブジェクトからの距離
	const Vector3 MDistance;

	// 親クラスのポインタ
	GameObject* mOwner;
};