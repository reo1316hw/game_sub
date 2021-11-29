#pragma once

/// <summary>
/// プレイヤーの頭上に攻撃するエフェクト
/// </summary>
class OverheadMagicEffect : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_bossPtr"> ボスのポインタ </param>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	/// <param name="_Scale"> 大きさ </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	OverheadMagicEffect(BossObject* _bossPtr, PlayerObject* _playerPtr, const Vector3& _Scale, const Tag& _ObjectTag);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~OverheadMagicEffect() {};

	/// <summary>
	/// オブジェクトの更新処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	// エフェクトの座標を更新しないタイミング
	const float MEffectPositionUnUpdateTiming;
	// 当たり判定を有効にするタイミング
	const float MBoxEnableTiming;
	// 当たり判定を無効にするタイミング
	const float MBoxDisableTiming;

	// 当たり判定の状態
	// true : 有効, false : 無効
	bool mIsCollisionState;
	// 1回だけ当たり判定を有効にするフラグ
	bool mIsOneCollisionState;
	// エフェクトを再生したか
	bool mIsPlayEffect;

	// 経過時間
	float mElapseTime;

	// ボスのポインタ
	BossObject* mBossPtr;
	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
	// エフェクトコンポーネントクラスのポインタ
	EffectComponent* mEffectComponentPtr;
};