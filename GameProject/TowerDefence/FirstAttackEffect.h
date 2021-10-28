#pragma once

/// <summary>
/// プレイヤーの1段階目の通常攻撃エフェクト
/// </summary>
class FirstAttackEffect : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	FirstAttackEffect(PlayerObject* _playerPtr, const Tag& _ObjectTag);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~FirstAttackEffect() {};

	/// <summary>
	/// オブジェクトの更新処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

	/// <summary>
	/// ヒットしたか確認
	/// </summary>
	/// <returns> ヒットしたか </returns>
	bool IsHitCheck() { return mIsHit == true; }

private:

	/// <summary>
	/// ヒットした時の処理
	/// </summary>
	/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
	void OnCollision(const GameObject& _HitObject)override;

	// ヒットフラグを有効にするタイミング
	const int MEnableIsHitTiming;

	// ヒットしたか
	bool mIsHit;
	// ヒットフラグを無効にするフラグ
	bool mDisableIsHit;

	// ヒットフラグを無効時間
	int mIsHitDisableCount;

	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
};