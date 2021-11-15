#pragma once

/// <summary>
/// 門
/// </summary>
class GateObject : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_Pos"> 座標 </param>
	/// <param name="_Scale"> 大きさ </param>
	/// <param name="_GpmeshName"> gpmeshのパス </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	GateObject(const Vector3& _Pos, const Vector3& _Scale, const std::string _GpmeshName, const Tag& _ObjectTag);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GateObject() {};

	/// <summary>
	/// オブジェクトの更新処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	// 門の右扉を丁度よい位置にずらすためのベクトル
	const Vector3 MRightGateDoorShiftVec;
	// 門の左扉を丁度よい位置にずらすためのベクトル
	const Vector3 MLeftGateDoorShiftVec;
};