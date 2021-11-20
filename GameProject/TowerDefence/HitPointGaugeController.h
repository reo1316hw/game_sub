#pragma once

/// <summary>
/// hpゲージを制御する
/// </summary>
class HitPointGaugeController : public Component
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> アタッチしたオブジェクトのポインタ </param>
	/// <param name="_gameObjectPtr"> 基底クラスのポインタ </param>
	HitPointGaugeController(GameObject* _owner, GameObject* _gameObjectPtr);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~HitPointGaugeController() {};

	/// <summary>
	/// フレーム毎の処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void Update(float _deltaTime)override;

private:

	// 現在の体力
	int mNowHp;

	// 最大体力
	float mMaxHp;

	// アタッチしたオブジェクトの初期の大きさ
	Vector3 mInitScale;

	// 基底クラスのポインタ
	GameObject* mGameObjectPtr;
};