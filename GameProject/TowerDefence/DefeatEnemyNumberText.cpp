#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Pos"> UIの生成場所(スクリーン座標) </param>
/// <param name="_ObjectTag"> アタッチしたゲームオブジェクトのタグ </param>
/// <param name="_State"> ゲームオブジェクトの状態 </param>
/// <param name="_FontDataNum"> フォントテクスチャ配列の要素数 </param>
/// <param name="_DefeatEnemyNum">  倒すエネミーの数 </param>
/// <param name="_enemysControlerPtr"> エネミーたちを制御するクラスのポインタ </param>
/// <param name="_Scale"> テクスチャの拡大サイズ </param>
DefeatEnemyNumberText::DefeatEnemyNumberText(const Vector3& _Pos, const Tag& _ObjectTag, const State& _State,
	const int& _FontDataNum, const int& _DefeatEnemyNum, EnemysControler* _enemysControlerPtr, const Vector3& _Scale)
	: GameObject(_ObjectTag)
{
	SetPosition(_Pos);
	SetScale(_Scale);
	SetState(_State);

	// テクスチャの取得
	Texture* texture = RENDERER->GetFontTexture(_FontDataNum);

	// スクリーン上に描画するコンポーネントクラス
	new SpriteComponent(this, texture);
	// 倒したエネミーをカウントするオブジェクトを無効にするコンポーネントを生成
	new DeadEnemyCounterDisable(this, _DefeatEnemyNum, _enemysControlerPtr);
}