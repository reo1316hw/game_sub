#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Pos"> UIの生成場所(スクリーン座標) </param>
/// <param name="_TextureName"> テクスチャのパス </param>
/// <param name="_ObjectTag"> アタッチしたゲームオブジェクトのタグ </param>
/// <param name="_bossPtr"> プレイヤーのポインタ </param>
/// <param name="_Scale"> 画像の拡大サイズ </param>
BossHitPointGauge::BossHitPointGauge(const Vector3& _Pos, const std::string& _TextureName, const Tag& _ObjectTag,
	BossObject* _bossPtr, const Vector2& _Scale)
	: GameObject(_ObjectTag)
	, mHitPointGaugeControllerPtr(nullptr)
	, mSpritePtr(nullptr)
{
	SetPosition(_Pos);

	// テクスチャの取得
	Texture* texture = RENDERER->GetTexture(_TextureName);

	// hpゲージを制御するコンポーネントクラス
	mHitPointGaugeControllerPtr = new HitPointGaugeController(_bossPtr, texture);

	// スクリーン上に描画するコンポーネントクラス
	mSpritePtr = new SpriteComponent(this, texture, mHitPointGaugeControllerPtr, _Scale);
}