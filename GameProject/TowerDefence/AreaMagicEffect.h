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

	// 高さ補正値
	const Vector3 MHeightCorrection;

	// ボスの現在のステート
	BossState mNowState;

	// ボスのポインタ
	BossObject* mBossPtr;
	// エフェクトコンポーネントクラスのポインタ
	EffectComponent* mEffectComponentPtr;
};