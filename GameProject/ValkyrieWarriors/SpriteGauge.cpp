#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチしたゲームオブジェクトのポインタ </param>
/// <param name="_Pos"> UIの生成場所(スクリーン座標) </param>
/// <param name="_TextureName"> テクスチャのパス </param>
/// <param name="_ObjectTag">ゲームオブジェクトのタグ </param>
/// <param name="_State"> ゲームオブジェクトの状態 </param>
/// <param name="_Scale"> 画像の拡大サイズ </param>
/// <param name="_IsInitScaleChange"> 最初にオブジェクトの大きさの変更を行うか </param>
SpriteGauge::SpriteGauge(GameObject* _owner, const Vector3& _Pos, const std::string& _TextureName,
	const Tag& _ObjectTag, const State& _State, const Vector3& _Scale, const bool& _IsInitScaleChange)
	: GameObject(_ObjectTag)
{
	SetPosition(_Pos);
	SetScale(_Scale);
	SetState(_State);

	// テクスチャの取得
	Texture* texture = RENDERER->GetTexture(_TextureName);

	// hpゲージを制御するコンポーネントクラス
	TextureSizeChanger* textureSizeChangerPtr = new TextureSizeChanger(this, _owner, _IsInitScaleChange);

	// スクリーン上に描画するコンポーネントクラス
	new SpriteComponent(this, texture);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチしたゲームオブジェクトのポインタ </param>
/// <param name="_Pos"> UIの生成場所(スクリーン座標) </param>
/// <param name="_TextureName"> テクスチャのパス </param>
/// <param name="_ObjectTag">ゲームオブジェクトのタグ </param>
/// <param name="_State"> ゲームオブジェクトの状態 </param>
/// <param name="_enemyObjectManagerPtr"> エネミーを管理するクラスの基底クラスのポインタ </param>
/// <param name="_Scale"> 画像の拡大サイズ </param>
/// <param name="_IsInitScaleChange"> 最初にオブジェクトの大きさの変更を行うか </param>
SpriteGauge::SpriteGauge(GameObject* _owner, const Vector3& _Pos, const std::string& _TextureName,
	const Tag& _ObjectTag, const State& _State, EnemyObjectManager* _enemyObjectManagerPtr,
	const Vector3& _Scale, const bool& _IsInitScaleChange)
	: GameObject(_ObjectTag)
{
	SetPosition(_Pos);
	SetScale(_Scale);
	SetState(_State);

	// テクスチャの取得
	Texture* texture = RENDERER->GetTexture(_TextureName);

	// hpゲージを制御するコンポーネントクラス
	TextureSizeChanger* textureSizeChangerPtr = new TextureSizeChanger(this, _owner, _IsInitScaleChange);

	// スクリーン上に描画するコンポーネントクラス
	new SpriteComponent(this, texture);

	// オブジェクトを無効にするコンポーネントを生成
	new ActiveObjectDisable(this, _enemyObjectManagerPtr);
}