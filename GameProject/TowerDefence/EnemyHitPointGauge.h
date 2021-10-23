#pragma once

// 前方宣言
class ParticleComponent;

/// <summary>
/// エネミーのhpゲージ
/// </summary>
class EnemyHitPointGauge : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_Scale"> 画像の拡大サイズ </param>
	/// <param name="_TextureName"> テクスチャのパス </param>
	/// <param name="_ObjectTag"> アタッチしたゲームオブジェクトのタグ </param>
	/// <param name="_enemyPtr"> プレイヤーのポインタ </param>
	EnemyHitPointGauge(const Vector3& _Scale, const std::string& _TextureName, 
		               const Tag& _ObjectTag, EnemyObject* _enemyPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyHitPointGauge() {};

	/// <summary>
	/// ゲームオブジェクトのアップデート
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	// エネミーからの距離ベクトル
	const Vector3 MOffset;

	// hpゲージを制御するコンポーネントクラスのポインタ
	HitPointGaugeController* mHitPointGaugeControllerPtr;
	// スクリーン上に描画するコンポーネントクラスのポインタ
	ParticleComponent* mParticlePtr;
	// エネミーのポインタ
	EnemyObject* mEnemyPtr;
};