#pragma once

/// <summary>
/// 操作説明UIの挙動
/// </summary>
class OperationExplanationBehavior : public Component
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> アタッチしたオブジェクトのポインタ </param>
	OperationExplanationBehavior(GameObject* _owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~OperationExplanationBehavior() {};

	/// <summary>
	/// フレーム毎の処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void Update(float _deltaTime)override;

private:

	// 初期座標
	const Vector3 MInitPosition;
};