#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Pos"> UIの生成場所(スクリーン座標) </param>
/// <param name="_TextureName"> テクスチャのパス </param>
/// <param name="_ObjectTag"> ゲームオブジェクトのタグ </param>
/// <param name="_Scale"> 画像の拡大サイズ </param>
OperationExplanation::OperationExplanation(const Vector3& _Pos, const std::string& _TextureName,
	const Tag& _ObjectTag, const Vector3& _Scale)
	: GameObject(_ObjectTag)
{
	SetPosition(_Pos);
	SetScale(_Scale);
	SetState(eActive);

	// テクスチャの取得
	Texture* texture = RENDERER->GetTexture(_TextureName);

	// スクリーン上に描画するコンポーネントクラス
	new SpriteComponent(this, texture);

	// 操作説明UIの挙動コンポーネントを生成
	new OperationExplanationBehavior(this);
}