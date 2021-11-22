#pragma once

// 前方宣言
class DeadObjectActiveBox;

/// <summary>
/// ボスが起動することによって出現する半透明の壁のを有効にするコンポーネント
/// </summary>
class DeadObjectEnable : public Component
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
	/// <param name="_activeForObjectPtr"> 更新させてないオブジェクトを更新させるためのオブジェクトの基底クラスのポインタ </param>
	/// <param name="_deadObjectPtr"> 更新させてないオブジェクトのポインタ </param>
	DeadObjectEnable(GameObject* _owner, GameObject* _activeForObjectPtr, GameObject* _deadObjectPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~DeadObjectEnable() {};

	/// <summary>
	/// フレーム毎の処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 < /param>
	void Update(float _deltaTime)override;

private:

	// 更新させてないオブジェクトを更新させるためのオブジェクトの基底クラスのポインタ
	GameObject* mActiveForObjectPtr;
	// 更新させてないオブジェクトのポインタ
	GameObject* mDeadObjectPtr;
};