#pragma once

/// <summary>
/// ボスのhpの枠
/// </summary>
class BossHitPointFrame : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_Pos"> UIの生成場所(スクリーン座標) </param>
	/// <param name="_TextureName"> テクスチャのパス </param>
	/// <param name="_ObjectTag"> ゲームオブジェクトのタグ </param>
	/// <param name="_Scale"> 画像の拡大サイズ </param>
	BossHitPointFrame(const Vector3& _Pos, const std::string& _TextureName,
		const Tag& _ObjectTag, const Vector3& _Scale = Vector3(1.0f, 1.0f, 1.0f));

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BossHitPointFrame() {};

private:
};