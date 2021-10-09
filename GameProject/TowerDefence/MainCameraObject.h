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
	MainCameraObject();

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
	//移動するための右スティックのしきい値
	const float MRightAxisThreshold;
	// 回転追加値
	const float MAddRotate;

	//追従先のオブジェクトを所持しているか
	bool mHasTarget;
      
	// カメラ周囲回転方向回転角
	float mRotateZAngle;
	// カメラ見降ろし方向回転角
	float mRotateYAngle;

	//親オブジェクトとの差
	Vector3 mOwnerOffset;
	//追従先のオブジェクト座標
	Vector3 mTargetPos;
	
public://セッターゲッター

	/// <summary>
	/// 見たい座標を設定
	/// </summary>
	/// <param name="_Offset"> 見たい座標との差 </param>
	/// <param name="_TargetPos"> 見る座標 </param>
	void SetViewObject(const Vector3& _Offset, const Vector3& _TargetPos);
};

