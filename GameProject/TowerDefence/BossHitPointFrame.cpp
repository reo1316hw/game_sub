#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Pos"> UIの生成場所(スクリーン座標) </param>
/// <param name="_TextureName"> テクスチャのパス </param>
/// <param name="_ObjectTag"> アタッチしたゲームオブジェクトのタグ </param>
/// <param name="_Scale"> 画像の拡大サイズ </param>
BossHitPointFrame::BossHitPointFrame(const Vector3& _Pos, const std::string& _TextureName,
	const Tag& _ObjectTag, const Vector2& _Scale)
	: GameObject(_ObjectTag)
	, mSpritePtr(nullptr)
{
	SetPosition(_Pos);
	SetState(eDead);

	// テクスチャの取得
	Texture* texture = RENDERER->GetTexture(_TextureName);

	// スクリーン上に描画するコンポーネントクラス
	mSpritePtr = new SpriteComponent(this, texture, _Scale);
}