#pragma once

// 前方宣言
class SpriteComponent;

/// <summary>
/// スプライトゲージのUI
/// </summary>
class SpriteGauge : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> アタッチしたゲームオブジェクトのポインタ </param>
	/// <param name="_Pos"> UIの生成場所(スクリーン座標) </param>
	/// <param name="_TextureName"> テクスチャのパス </param>
	/// <param name="_State"> ゲームオブジェクトの状態 </param>
	/// <param name="_ObjectTag"> ゲームオブジェクトのタグ </param>
	/// <param name="_Scale"> テクスチャの拡大サイズ </param>
	/// <param name="_IsInitScaleChange"> 最初にオブジェクトの大きさの変更を行うか </param>
	SpriteGauge(GameObject* _owner, const Vector3& _Pos, const std::string& _TextureName,
		const Tag& _ObjectTag, const State& _State, const Vector3& _Scale = Vector3(1.0f, 1.0f, 1.0f), 
		const bool& _IsInitScaleChange = false);

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> アタッチしたゲームオブジェクトのポインタ </param>
	/// <param name="_Pos"> UIの生成場所(スクリーン座標) </param>
	/// <param name="_TextureName"> テクスチャのパス </param>
	/// <param name="_State"> ゲームオブジェクトの状態 </param>
	/// <param name="_ObjectTag"> ゲームオブジェクトのタグ </param>
	/// <param name="_enemyObjectManagerPtr"> エネミーを管理するクラスの基底クラスのポインタ </param>
	/// <param name="_Scale"> テクスチャの拡大サイズ </param>
	/// <param name="_IsInitScaleChange"> 最初にオブジェクトの大きさの変更を行うか </param>
	SpriteGauge(GameObject* _owner, const Vector3& _Pos, const std::string& _TextureName, 
		const Tag& _ObjectTag, const State& _State, EnemyObjectManager* _enemyObjectManagerPtr,
		const Vector3& _Scale = Vector3(1.0f, 1.0f, 1.0f), const bool& _IsInitScaleChange = false);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SpriteGauge() {};

private:
};