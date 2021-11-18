#pragma once

/// <summary>
/// プレイヤーのhpの枠
/// </summary>
class PlayerHitPointFrame : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_Pos"> UIの生成場所(スクリーン座標) </param>
	/// <param name="_TextureName"> テクスチャのパス </param>
	/// <param name="_ObjectTag"> ゲームオブジェクトのタグ </param>
	/// <param name="_Scale"> テクスチャの拡大サイズ </param>
	PlayerHitPointFrame(const Vector3& _Pos, const std::string& _TextureName,
		 const Tag& _ObjectTag, const Vector2& _Scale = Vector2(1.0f, 1.0f));

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerHitPointFrame() {};

private:
};