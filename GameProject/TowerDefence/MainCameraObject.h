#pragma once

/// <summary>
/// メインカメラ
/// </summary>
class MainCameraObject : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
    /// <param name="_playerPtr"> プレイヤーのポインタ </param>
	/// <param name="_bossPtr"> ボスのポインタ </param>
    /// <param name="_ReUseGameObject"> 再利用するかのフラグ </param>
	MainCameraObject(PlayerObject* _playerPtr, BossObject* _bossPtr, const bool& _ReUseGameObject);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MainCameraObject() {};

	/// <summary>
	/// オブジェクトの更新処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

	/// <summary>
	/// 入力を引数で受け取る更新関数
	/// 基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
	/// </summary>
	/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
	void GameObjectInput(const InputState& _KeyState)override;

private:

	// 最小仰角
	const float MMinLookDownAngle;
	// 最大仰角
	const float MMaxLookDownAngle;
	// 動するための右スティックのしきい値
	const float MRightAxisThreshold;
	// 回転追加値
	const float MAddRotate;
	// カメラ座標との差
	const Vector3 MCameraOffset;
	// 見たい座標との差
	const Vector3 MTargetOffset;
      
	// カメラ周囲回転方向回転角
	float mRotateZAngle;
	// カメラ見降ろし方向回転角
	float mRotateYAngle;

	// 追従先のオブジェクト座標
	Vector3 mTargetPos;
	// 初期座標
	Vector3 mInitPosition;

	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
	// ボスのポインタ
	BossObject* mBossPtr;
};

