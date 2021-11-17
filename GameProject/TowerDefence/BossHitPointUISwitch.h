#pragma once

/// <summary>
/// ボスの体力UIのON/OFFを行うコンポーネント
/// </summary>
class BossHitPointUISwitch : public Component
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
	/// <param name="_bossActiveBoxPtr"> ボスを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
	/// <param name="_bossHitPointGaugePtr"> ボスのhpゲージのポインタ </param>
	/// <param name="_bossHitPointFramePtr"> ボスのhpの枠のポインタ </param>
	BossHitPointUISwitch(GameObject* _owner, BossActiveBox* _bossActiveBoxPtr,
		BossHitPointGauge* _bossHitPointGaugePtr, BossHitPointFrame* _bossHitPointFramePtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BossHitPointUISwitch() {};

	/// <summary>
	/// フレーム毎の処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 < /param>
	void Update(float _deltaTime)override;

private:

	// ボスを更新させるための当たり判定用矩形オブジェクトのポインタ
	BossActiveBox* mBossActiveBoxPtr;
	// ボスのhpゲージのポインタ
	BossHitPointGauge* mBossHitPointGaugePtr;
	// ボスのhpの枠のポインタ
	BossHitPointFrame* mBossHitPointFramePtr;
};