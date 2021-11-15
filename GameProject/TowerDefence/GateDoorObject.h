#pragma once

/// <summary>
/// 門の扉
/// </summary>
class GateDoorObject : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_Pos"> 座標 </param>
	/// <param name="_Scale"> 大きさ </param>
	/// <param name="_GpmeshName"> gpmeshのパス </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	GateDoorObject(const Vector3& _Pos, const Vector3& _Scale,
		const std::string _GpmeshName, const Tag& _ObjectTag);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GateDoorObject() {};

private:
};