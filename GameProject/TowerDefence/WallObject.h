#pragma once

// 前方宣言
class MeshComponent;
class Mesh;
class BoxCollider;

/// <summary>
/// 壁
/// </summary>
class WallObject : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_Pos"> 座標 </param>
	/// <param name="_Scale"> 大きさ </param>
	/// <param name="_GpmeshName"> gpmeshのパス </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	WallObject(const Vector3& _Pos, const Vector3& _Scale, const std::string _GpmeshName, const Tag& _ObjectTag);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~WallObject() {};

	/// <summary>
	/// オブジェクトの更新処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

private:
};