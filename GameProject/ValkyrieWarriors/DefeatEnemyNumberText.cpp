#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Pos"> UIの生成場所(スクリーン座標) </param>
/// <param name="_ObjectTag"> アタッチしたゲームオブジェクトのタグ </param>
/// <param name="_State"> ゲームオブジェクトの状態 </param>
/// <param name="_FontDataNum"> フォントテクスチャ配列の要素数 </param>
/// <param name="_enemyObjectManagerPtr"> エネミーを管理するクラスの基底クラスのポインタ </param>
/// <param name="_Scale"> テクスチャの拡大サイズ </param>
DefeatEnemyNumberText::DefeatEnemyNumberText(const Vector3& _Pos, const Tag& _ObjectTag, const State& _State,
	const int& _FontDataNum, EnemyObjectManager* _enemyObjectManagerPtr, const Vector3& _Scale)
	: GameObject(_ObjectTag)
{
	SetPosition(_Pos);
	SetScale(_Scale);
	SetState(_State);

	// テクスチャの取得
	Texture* texture = RENDERER->GetFontTexture(_FontDataNum);

	// スクリーン上に描画するコンポーネントクラス
	new SpriteComponent(this, texture);
	// オブジェクトを無効にするコンポーネントを生成
	new ActiveObjectDisable(this, _enemyObjectManagerPtr);
}