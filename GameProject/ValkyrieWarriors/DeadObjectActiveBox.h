#pragma once

/// <summary>
/// 更新していないオブジェクトを更新させるための当たり判定用矩形オブジェクト
/// </summary>
class DeadObjectActiveBox : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_Pos"> 座標 </param>
	/// <param name="_Scale"> 大きさ </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	DeadObjectActiveBox(const Vector3& _Pos, const Vector3& _Scale, const Tag& _ObjectTag);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~DeadObjectActiveBox() {};

	/// <summary>
	/// オブジェクトの更新処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

	/// <summary>
	/// ヒットした時の処理
	/// </summary>
	/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
	void OnCollision(const GameObject& _HitObject)override;

private:

	// プレイヤーと当たったか
	bool mIsHitPlayer;
	// 有効にするかのフラグ
	bool mIsEnable;
};