#pragma once

// 前方宣言
class ParticleComponent;

/// <summary>
/// パーティクルゲージのUI
/// </summary>
class ParticleGauge : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> アタッチしたゲームオブジェクトのポインタ </param>
	/// <param name="_Scale"> 画像の拡大サイズ </param>
	/// <param name="_TextureName"> テクスチャのパス </param>
	/// <param name="_ObjectTag"> ゲームオブジェクトのタグ </param>
	/// <param name="_IsInitScaleChange"> 最初にオブジェクトの大きさの変更を行うか </param>
	ParticleGauge(GameObject* _owner, const Vector3& _Scale,
		const std::string& _TextureName, const Tag& _ObjectTag,
		const bool& _IsInitScaleChange = false);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParticleGauge() {};

	/// <summary>
	/// ゲームオブジェクトのアップデート
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	// エネミーからの距離ベクトル
	const Vector3 MOffset;

	// アタッチしたゲームオブジェクトのポインタ
	GameObject* mOwner;
};
