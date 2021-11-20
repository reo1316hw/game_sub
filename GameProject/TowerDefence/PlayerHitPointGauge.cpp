#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Pos"> UIの生成場所(スクリーン座標) </param>
/// <param name="_TextureName"> テクスチャのパス </param>
/// <param name="_ObjectTag"> アタッチしたゲームオブジェクトのタグ </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
/// <param name="_Scale"> テクスチャの拡大サイズ </param>
PlayerHitPointGauge::PlayerHitPointGauge(const Vector3& _Pos, const std::string& _TextureName, const Tag& _ObjectTag,
	PlayerObject* _playerPtr, const Vector3& _Scale)
	: GameObject(_ObjectTag)
{
	SetPosition(_Pos);
	SetScale(_Scale);

	// テクスチャの取得
	Texture* texture = RENDERER->GetTexture(_TextureName);

	// hpゲージを制御するコンポーネントクラス
	HitPointGaugeController* hitPointGaugeControllerPtr = new HitPointGaugeController(this, _playerPtr);

	// スクリーン上に描画するコンポーネントクラス
	new SpriteComponent(this, texture);
}