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
	/// <param name="_AddAngle"> 回転角を増やすための定数 </param>
	/// <param name="_GpmeshName"> gpmeshのパス </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	/// <param name="_enemysControlerPtr"> エネミーを制御するコンポーネントクラスのポインタ </param>
	GateDoorObject(const Vector3& _Pos, const Vector3& _Scale, const float _AddAngle,
		const std::string _GpmeshName, const Tag& _ObjectTag, EnemysControler* _enemysControlerPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GateDoorObject() {};

	/// <summary>
	/// オブジェクトの更新処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	/// <summary>
	/// 回転処理
	/// </summary>
	/// <param name="_Axis"> 軸 </param>
	/// <param name="_Angle"> 角度 </param>
	void SelfRotation(const Vector3& _Axis, const float& _Angle);
	
	// 回転角を増やすための定数
	const float MAddAngle;

	// 回転角
	float mAngle;

	// エネミーを制御するコンポーネントクラスのポインタ
	EnemysControler* mEnemysControlerPtr;
};