#pragma once

// 前方宣言
class GameObject;

/// <summary>
/// コンポーネントの基底クラス
/// </summary>
class Component
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
	/// <param name="_UpdateOrder"> コンポーネントの更新順番（数値が小さいほど早く更新される） </param>
	Component(GameObject* _owner, const int _UpdateOrder = 100);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Component();

	/// <summary>
	/// フレーム毎の処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 < /param>
	virtual void Update(float _deltaTime) {};

	/// <summary>
	/// 入力処理
	/// </summary>
	/// <param name="_state"> InputState構造体 </param>
	virtual void ProcessInput(const struct InputState& _state) {}

	/// <summary>
	/// Transformのワールド変換
	/// </summary>
	virtual void OnUpdateWorldTransform() {}

protected:

	// コンポーネントの更新順番（数値が小さいほど早く更新される）
	int mUpdateOrder;

	// アタッチしているゲームオブジェクトのポインタ
	GameObject* mOwner;			
	
public://ゲッターセッター

	/// <summary>
	/// 更新順番を取得
	/// </summary>
	/// <returns> 更新順番 </returns>
	int GetUpdateOder() { return mUpdateOrder; }

	/// <summary>
	/// アタッチしているゲームオブジェクトへのポインタを取得
	/// </summary>
	/// <returns> アタッチしているゲームオブジェクトへのポインタ </returns>
	GameObject* GetOwner() { return mOwner; }
};