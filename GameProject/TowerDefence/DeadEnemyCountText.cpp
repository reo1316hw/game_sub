#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Pos"> UIの生成場所(スクリーン座標) </param>
/// <param name="_ObjectTag"> アタッチしたゲームオブジェクトのタグ </param>
/// <param name="_Scale"> テクスチャの拡大サイズ </param>
DeadEnemyCountText::DeadEnemyCountText(const Vector3& _Pos, const Tag& _ObjectTag, const Vector2& _Scale)
	: GameObject(_ObjectTag)
{
	SetPosition(_Pos);

	// テクスチャの取得
	Texture* texture = RENDERER->GetFontTexture(101);

	// スクリーン上に描画するコンポーネントクラス
	new SpriteComponent(this, texture, _Scale);
}