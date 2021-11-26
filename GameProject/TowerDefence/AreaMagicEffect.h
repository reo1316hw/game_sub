#pragma once

/// <summary>
/// 範囲攻撃エフェクト
/// </summary>
class AreaMagicEffect : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_bossPtr"> ボスのポインタ </param>
	/// <param name="_Scale"> 大きさ </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	AreaMagicEffect(BossObject* _bossPtr, const Vector3& _Scale, const Tag& _ObjectTag);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~AreaMagicEffect() {};

	/// <summary>
	/// オブジェクトの更新処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	// 当たり判定を有効にするタイミング
	const float MBoxEnableTiming;
	// 当たり判定を無効にするタイミング
	const float MBoxDisableTiming;

	// 高さ補正値
	const Vector3 MHeightCorrection;

	// 当たり判定の状態
	// true : 有効, false : 無効
	bool mIsCollisionState;
	// 1回だけ当たり判定を有効にするフラグ
	bool mIsOneCollisionState;

	// 経過時間
	float mElapseTime;

	// ボスの現在のステート
	BossState mNowState;

	// ボスのポインタ
	BossObject* mBossPtr;
	// エフェクトコンポーネントクラスのポインタ
	EffectComponent* mEffectComponentPtr;
};