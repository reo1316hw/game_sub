#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Pos"> UIの生成場所(スクリーン座標) </param>
/// <param name="_TextureName"> テクスチャのパス </param>
/// <param name="_ObjectTag"> アタッチしたゲームオブジェクトのタグ </param>
/// <param name="_bossPtr"> プレイヤーのポインタ </param>
/// <param name="_Scale"> 画像の拡大サイズ </param>
ParticleGauge::ParticleGauge(const Vector3& _Pos, const std::string& _TextureName, const Tag& _ObjectTag,
	BossObject* _bossPtr, const Vector3& _Scale)
	: GameObject(_ObjectTag)
{
	SetPosition(_Pos);
	SetScale(_Scale);
	SetState(eDead);

	// テクスチャの取得
	Texture* texture = RENDERER->GetTexture(_TextureName);

	// hpゲージを制御するコンポーネントクラス
	TextureSizeChanger* textureSizeChangerPtr = new TextureSizeChanger(this, _bossPtr);

	// スクリーン上に描画するコンポーネントクラス
	new SpriteComponent(this, texture);
}