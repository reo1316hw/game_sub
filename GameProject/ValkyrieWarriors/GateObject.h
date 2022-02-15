#pragma once

// 前方宣言
class GateDoorObject;

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
	/// <param name="_OpenToEnemyDefeatNum"> 門を開くために倒すエネミーの数 </param>
	/// <param name="_GpmeshName"> gpmeshのパス </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	/// <param name="_enemysControlerPtr"> エネミーを制御するコンポーネントクラスのポインタ </param>
	GateObject(const Vector3& _Pos, const Vector3& _Scale, const int& _OpenToDefeatEnemyNum,
		const std::string _GpmeshName, const Tag& _ObjectTag, EnemysControler* _enemysControlerPtr);

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

	// 矩形当たり判定の数
	const int BoxColliderNum;

	// 門の右扉の回転角を増やすための定数
	const float MRightGateDoorAddAngle;
	// 門の左扉の回転角を増やすための定数
	const float MLeftGateDoorAddAngle;

	// 門の右扉を丁度よい位置にずらすためのベクトル
	const Vector3 MRightGateDoorShiftVec;
	// 門の左扉を丁度よい位置にずらすためのベクトル
	const Vector3 MLeftGateDoorShiftVec;

	// 門の扉のポインタ
	GateDoorObject* mGateDoorPtr;

public:// ゲッターセッター

	/// <summary>
	/// 門の扉のポインタを取得
	/// </summary>
	/// <returns> 門の扉のポインタ </returns>
	GateDoorObject* GetGateDoorPtr() { return mGateDoorPtr; }
};