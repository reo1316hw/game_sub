#pragma once

// 前方宣言
class SpriteComponent;

/// <summary>
/// プレイヤーのhpゲージ
/// </summary>
class PlayerHitPointGauge : public GameObject
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
	PlayerHitPointGauge(const Vector3& _Pos, const std::string& _TextureName, const Tag& _ObjectTag,
		                PlayerObject* _playerPtr, const float& _Scale = 1.0f);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerHitPointGauge() {};

private:

	// hpゲージを制御するコンポーネントクラスのポインタ
	HitPointGaugeController* mHitPointGaugeControllerPtr;
	// スクリーン上に描画するコンポーネントクラスのポインタ
	SpriteComponent* mSpritePtr;
};