#pragma once

// 前方宣言
class DeadObjectActiveBox;

/// <summary>
/// ボスが起動することによって出現する半透明の壁のON/OFFを行うコンポーネント
/// </summary>
class DeadObjectSwitch : public Component
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
	/// <param name="_bossActiveBoxPtr"> 更新させてないオブジェクトを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
	/// <param name="_deadObjectPtr"> 更新させてないオブジェクトのポインタ </param>
	DeadObjectSwitch(GameObject* _owner, DeadObjectActiveBox* _deadObjectActiveBoxPtr, GameObject* _deadObjectPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~DeadObjectSwitch() {};

	/// <summary>
	/// フレーム毎の処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 < /param>
	void Update(float _deltaTime)override;

private:

	// 更新させてないオブジェクトを更新させるための当たり判定用矩形オブジェクトのポインタ
	DeadObjectActiveBox* mDeadObjectActiveBoxPtr;
	// 更新させてないオブジェクトのポインタ
	GameObject* mDeadObjectPtr;
};