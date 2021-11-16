#pragma once

// 前方宣言
class SelfRotation;

/// <summary>
/// 門を開く
/// </summary>
class OpenGate : public Component
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
	/// <param name="_Axis"> 軸 </param>
	/// <param name="_AddAngle"> 回転角を増やすための定数 </param>
	/// <param name="_OpenToEnemyDefeatNum"> 門を開くために倒すエネミーの数 </param>
	/// <param name="_enemysControlerPtr"> エネミーを制御するコンポーネントクラスのポインタ </param>
	/// <param name="_selfRotationPtr"> 自身を回転するためのコンポーネントクラスのポインタ </param>
	OpenGate(GameObject* _owner, const Vector3& _Axis, const float& _AddAngle, const int& _OpenToDefeatEnemyNum,
		EnemysControler* _enemysControlerPtr, SelfRotation* _selfRotationPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~OpenGate() {};

	/// <summary>
	/// フレーム毎の処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void Update(float _deltaTime)override;

private:

	// 門を開くために倒すエネミーの数
	const int& MOpenToDefeatEnemyNum;

	// 回転角を増やすための定数
	const float MAddAngle;
	// 門が開く角度
	const float MOpenAngle;

	// 回転軸
	const Vector3& MAxis;
	
	// 回転角
	float mAngle;

	// エネミーを制御するコンポーネントクラスのポインタ
	EnemysControler* mEnemysControlerPtr;
	// 自身を回転するためのコンポーネントクラスのポインタ
	SelfRotation* mSelfRotationPtr;
};