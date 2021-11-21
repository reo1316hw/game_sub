#pragma once

/// <summary>
/// hpゲージを制御する
/// </summary>
class TextureSizeChanger : public Component
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> アタッチしたオブジェクトのポインタ </param>
	/// <param name="_gameObjectPtr"> 基底クラスのポインタ </param>
	/// <param name="_IsInitScaleChange"> 最初にオブジェクトの大きさの変更を行うか </param>
	TextureSizeChanger(GameObject* _owner, GameObject* _gameObjectPtr, const bool& _IsInitScaleChange);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~TextureSizeChanger() {};

	/// <summary>
	/// フレーム毎の処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void Update(float _deltaTime)override;

private:

	// 現在のスケールサイズを求めるための左辺の値
	int mNowScaleLeftSideValue;

	// スケールサイズを求めるための右辺の値
	float mScaleRightSideValue;

	// アタッチしたオブジェクトの初期の大きさ
	Vector3 mInitScale;

	// 基底クラスのポインタ
	GameObject* mGameObjectPtr;
};