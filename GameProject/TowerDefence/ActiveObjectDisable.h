#pragma once

/// <summary>
/// 倒したエネミーをカウントするオブジェクトを無効にするクラス
/// </summary>
class ActiveObjectDisable : public Component
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
	/// <param name="_deadForObjectPtr"> 更新しているオブジェクトを更新させないようにするためのオブジェクトの基底クラスのポインタ </param>
	ActiveObjectDisable(GameObject* _owner, GameObject* _deadForObjectPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ActiveObjectDisable() {};

	/// <summary>
	/// フレーム毎の処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 < /param>
	void Update(float _deltaTime)override;

private:

	// 更新しているオブジェクトを更新させないようにするためのオブジェクトの基底クラスのポインタ
	GameObject* mDeadForObjectPtr;
};

