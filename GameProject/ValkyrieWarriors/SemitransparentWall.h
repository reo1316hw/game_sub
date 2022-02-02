#pragma once

/// <summary>
/// 半透明の壁
/// </summary>
class SemitransparentWall : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_Pos"> 座標 </param>
	/// <param name="_Scale"> 大きさ </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	SemitransparentWall(const Vector3& _Pos, const Vector3& _Scale, const Tag& _ObjectTag);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SemitransparentWall() {};

	/// <summary>
	/// オブジェクトの更新処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

private:
};