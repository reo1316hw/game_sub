#pragma once

/// <summary>
/// 前方攻撃エフェクト(中核の部分)
/// </summary>
class FrontCoreMagicEffect : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_bossPtr"> ボスのポインタ </param>
	/// <param name="_Scale"> 大きさ </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	FrontCoreMagicEffect(BossObject* _bossPtr, const Vector3& _Scale, const Tag& _ObjectTag);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~FrontCoreMagicEffect() {};

	/// <summary>
	/// オブジェクトの更新処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	// 当たり判定を有効にするタイミング
	const float MBoxEnableTiming;
	
	// 速度の値
	const float MMoveSpeed;

	// 高さ補正値
	const Vector3 MHeightCorrection;

	// 経過時間
	float mElapseTime;

	// ボスのポインタ
	BossObject* mBossPtr;
	// エフェクトコンポーネントクラスのポインタ
	EffectComponent* mEffectComponentPtr;
};