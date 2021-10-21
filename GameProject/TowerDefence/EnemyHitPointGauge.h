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
	/// <param name="_Pos"> UIの生成場所(スクリーン座標) </param>
	/// <param name="_TextureName"> テクスチャのパス </param>
	/// <param name="_ObjectTag"> アタッチしたゲームオブジェクトのタグ </param>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	/// <param name="_Scale"> 画像の拡大サイズ </param>
	EnemyHitPointGauge(const Vector3& _Pos, const std::string& _TextureName, const Tag& _ObjectTag,
		               PlayerObject* _playerPtr, const float& _Scale = 10.0f);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyHitPointGauge() {};

private:

	// hpゲージを制御するコンポーネントクラスのポインタ
	HitPointGaugeController* mHitPointGaugeControllerPtr;
	// スクリーン上に描画するコンポーネントクラスのポインタ
	ParticleComponent* mParticlePtr;
};