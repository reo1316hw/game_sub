#pragma once

/// <summary>
/// プレイヤーの1段階目の通常攻撃エフェクト
/// </summary>
class DashAttackEffect : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	/// <param name="_Scale"> 大きさ </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	/// <param name="_dashAttackPtr"> ダッシュ攻撃状態のクラスのポインタ </param>
	DashAttackEffect(PlayerObject* _playerPtr, const Vector3& _Scale, const Tag& _ObjectTag, PlayerObjectStateDashAttack* _dashAttackPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~DashAttackEffect() {};

	/// <summary>
	/// オブジェクトの更新処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

	/// <summary>
	/// ヒットした時の処理
	/// </summary>
	/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
	void OnCollision(const GameObject& _HitObject)override;

	/// <summary>
	/// ヒットしたか確認
	/// </summary>
	/// <returns> ヒットしたか </returns>
	bool IsHitCheck() { return mIsHit == true; }

private:

	// 座標との差
	const float MOffset;
	// 高さの補正値
	const Vector3 MHeightCorrection;

	// ヒットしたか
	bool mIsHit;
	// ヒットフラグを無効にするフラグ
	bool mDisableIsHit;

	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
	// エフェクトコンポーネントクラスのポインタ
	EffectComponent* mEffectComponentPtr;
	// ダッシュ攻撃状態のクラスのポインタ
	PlayerObjectStateDashAttack* mDashAttackPtr;
};