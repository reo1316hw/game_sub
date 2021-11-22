#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Pos"> UIの生成場所(スクリーン座標) </param>
/// <param name="_ObjectTag"> アタッチしたゲームオブジェクトのタグ </param>
/// <param name="_enemyObjectManagerPtr"> エネミーを管理するクラスの基底クラスのポインタ </param>
/// <param name="_Scale"> テクスチャの拡大サイズ </param>
DeadEnemyCountText::DeadEnemyCountText(const Vector3& _Pos, const Tag& _ObjectTag,
	EnemyObjectManager* _enemyObjectManagerPtr, const Vector3& _Scale)
	: GameObject(_ObjectTag)
{
	SetPosition(_Pos);
	SetScale(_Scale);

	// テクスチャの取得
	Texture* texture = RENDERER->GetFontTexture(0);

	// スクリーン上に描画するコンポーネントクラスを生成
	SpriteComponent* spriteComponentPtr = new SpriteComponent(this, texture);
	// 倒したエネミーのカウントUIのテクスチャを変えるクラスを生成
	new DeadEnemyCountTextChange(this, spriteComponentPtr, _enemyObjectManagerPtr->GetEnemysControlerPtr());
	// 倒したエネミーをカウントするオブジェクトを無効にするコンポーネントを生成
	new ActiveObjectDisable(this, _enemyObjectManagerPtr);
}