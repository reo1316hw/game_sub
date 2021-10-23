#pragma once

// 前方宣言
class SpriteComponent;

/// <summary>
/// ボスのhpゲージ
/// </summary>
class BossHitPointGauge : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_Pos"> UIの生成場所(スクリーン座標) </param>
	/// <param name="_TextureName"> テクスチャのパス </param>
	/// <param name="_ObjectTag"> アタッチしたゲームオブジェクトのタグ </param>
	/// <param name="_bossPtr"> プレイヤーのポインタ </param>
	/// <param name="_Scale"> 画像の拡大サイズ </param>
	BossHitPointGauge(const Vector3& _Pos, const std::string& _TextureName, const Tag& _ObjectTag,
		              BossObject* _bossPtr, const float& _Scale = 1.0f);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BossHitPointGauge() {};

private:

	// hpゲージを制御するコンポーネントクラスのポインタ
	HitPointGaugeController* mHitPointGaugeControllerPtr;
	// スクリーン上に描画するコンポーネントクラスのポインタ
	SpriteComponent* mSpritePtr;
};