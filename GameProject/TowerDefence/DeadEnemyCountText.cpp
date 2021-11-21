#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Pos"> UIの生成場所(スクリーン座標) </param>
/// <param name="_ObjectTag"> アタッチしたゲームオブジェクトのタグ </param>
/// <param name="_enemysControlerPtr"> エネミーたちを制御するクラスのポインタ </param>
/// <param name="_Scale"> テクスチャの拡大サイズ </param>
DeadEnemyCountText::DeadEnemyCountText(const Vector3& _Pos, const Tag& _ObjectTag,
	EnemysControler* _enemysControlerPtr, const Vector3& _Scale)
	: GameObject(_ObjectTag)
{
	SetPosition(_Pos);
	SetScale(_Scale);

	// テクスチャの取得
	Texture* texture = RENDERER->GetFontTexture(0);

	// スクリーン上に描画するコンポーネントクラスを生成
	SpriteComponent* spriteComponentPtr = new SpriteComponent(this, texture);
	// 倒したエネミーのカウントUIのテクスチャを変えるクラスを生成
	new DeadEnemyCountTextChange(this, spriteComponentPtr, _enemysControlerPtr);
	// 倒したエネミーをカウントするオブジェクトを無効にするコンポーネントを生成
	new DeadEnemyCounterDisable(this, _enemysControlerPtr);
}