#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Pos"> UIの生成場所(スクリーン座標) </param>
/// <param name="_TextureName"> テクスチャのパス </param>
/// <param name="_ObjectTag"> アタッチしたゲームオブジェクトのタグ </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
/// <param name="_Scale"> 画像の拡大サイズ </param>
EnemyHitPointGauge::EnemyHitPointGauge(const Vector3& _Pos, const std::string& _TextureName, const Tag& _ObjectTag,
	PlayerObject* _playerPtr, const float& _Scale)
	: GameObject(_ObjectTag)
	, mHitPointGaugeControllerPtr(nullptr)
	, mParticlePtr(nullptr)
{
	SetPosition(_Pos);

	//　テクスチャの取得
	Texture* texture = RENDERER->GetTexture(_TextureName);

	// hpゲージを制御するコンポーネントクラス
	mHitPointGaugeControllerPtr = new HitPointGaugeController(_playerPtr, texture);

	// スクリーン上に描画するコンポーネントクラス
	mParticlePtr = new ParticleComponent(this, mHitPointGaugeControllerPtr);
	mParticlePtr->SetTexture(texture);
}