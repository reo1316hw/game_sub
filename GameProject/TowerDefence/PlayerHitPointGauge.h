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
	/// <param name="_Scale"> テクスチャの拡大サイズ </param>
	PlayerHitPointGauge(const Vector3& _Pos, const std::string& _TextureName, const Tag& _ObjectTag,
		                PlayerObject* _playerPtr, const Vector2& _Scale = Vector2(1.0f,1.0f));

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