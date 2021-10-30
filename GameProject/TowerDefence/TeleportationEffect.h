#pragma once

/// <summary>
/// テレポートエフェクト
/// </summary>
class TeleportationEffect : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_bossPtr"> ボスのポインタ </param>
	/// <param name="_Scale"> 大きさ </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	TeleportationEffect(BossObject* _bossPtr, const Vector3& _Scale, const Tag& _ObjectTag);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TeleportationEffect() {};

	/// <summary>
	/// オブジェクトの更新処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	// エフェクト再生速度
	const float MPlayRate;
	// 高さ補正値
	const Vector3 MHeightCorrection;

	// ボスの現在のステート
	BossState mNowState;

	// ボスのポインタ
	BossObject* mBossPtr;
	// エフェクトコンポーネントクラスのポインタ
	EffectComponent* mEffectComponentPtr;
};