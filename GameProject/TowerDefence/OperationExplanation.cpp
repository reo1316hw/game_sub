#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Pos"> UIの生成場所(スクリーン座標) </param>
/// <param name="_TextureName"> テクスチャのパス </param>
/// <param name="_ObjectTag"> ゲームオブジェクトのタグ </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
/// <param name="_Scale"> 画像の拡大サイズ </param>
OperationExplanation::OperationExplanation(const Vector3& _Pos, const std::string& _TextureName,
	const Tag& _ObjectTag, PlayerObject* _playerPtr, const Vector3& _Scale)
	: GameObject(_ObjectTag)
{
	SetPosition(_Pos);
	SetScale(_Scale);
	SetState(eDead);

	// テクスチャの取得
	Texture* texture = RENDERER->GetTexture(_TextureName);

	// スクリーン上に描画するコンポーネントクラス
	new SpriteComponent(this, texture);

	// 操作説明UIの挙動コンポーネントを生成
	new OperationExplanationBehavior(this, _playerPtr);

	// オブジェクトを無効にするコンポーネントを生成
	new ActiveObjectDisable(this, this);
}