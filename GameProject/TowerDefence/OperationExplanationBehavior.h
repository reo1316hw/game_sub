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
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	OperationExplanationBehavior(GameObject* _owner, PlayerObject* _playerPtr);

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

	// 移動速度
	const float MMoveSpeed;
	// 止めるための距離
	const float MStopForDistance;

	// 初期座標
	const Vector3 MInitPosition;
	// 右向きのベクトル
	const Vector3 MRightDirVec;
	// 左向きのベクトル
	const Vector3 MLeftDirVec;

	// 無効にするかのフラグ
	bool mIsDisable;

	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
};