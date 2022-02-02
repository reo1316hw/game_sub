#pragma once

/// <summary>
/// ヒットエフェクト
/// </summary>
class HitEffect : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> 親クラスのポインタ </param>
	/// <param name="_Scale"> 大きさ </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	HitEffect(GameObject* _owner, const Vector3& _Scale, const Tag& _ObjectTag);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~HitEffect() {};

	/// <summary>
	/// オブジェクトの更新処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	// 高さ補正値
	const Vector3 MHeightCorrection;

	// 現在のhp
	int mNowHp;

	// プレイヤーのポインタ
	GameObject* mOwner;
	// エフェクトコンポーネントクラスのポインタ
	EffectComponent* mEffectComponentPtr;
};