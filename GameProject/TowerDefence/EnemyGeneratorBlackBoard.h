#pragma once

/// <summary>
/// エネミー生成器の中身の黒い部分
/// </summary>
class EnemyGeneratorBlackBoard : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_Pos"> 座標 </param>
	/// <param name="_Scale"> 大きさ </param>
    /// <param name="_Angle"> 回転角 </param>
	/// <param name="_GpmeshName"> gpmeshのパス </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	EnemyGeneratorBlackBoard(const Vector3& _Pos, const Vector3& _Scale, const float& _Angle,
		const std::string _GpmeshName, const Tag& _ObjectTag);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyGeneratorBlackBoard() {};

private:

	/// <summary>
	/// 回転処理
	/// </summary>
	/// <param name="_Axis"> 軸 </param>
	/// <param name="_Angle"> 角度 </param>
	void SelfRotation(const Vector3& _Axis, const float& _Angle);
};