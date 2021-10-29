#pragma once

/// <summary>
/// プレイヤーの1段階目の通常攻撃エフェクト
/// </summary>
class ThirdAttackEffect : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	/// <param name="_Scale"> 大きさ </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	/// <param name="_thirdAttackPtr"> 3段階目の通常攻撃状態のクラスのポインタ </param>
	ThirdAttackEffect(PlayerObject* _playerPtr, const Vector3& _Scale, const Tag& _ObjectTag, PlayerObjectStateThirdAttack* _thirdAttackPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ThirdAttackEffect() {};

	/// <summary>
	/// オブジェクトの更新処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	// 座標との差
	const float MOffset;
	// 高さの補正値
	const Vector3 MHeightCorrection;

	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
	// エフェクトコンポーネントクラスのポインタ
	EffectComponent* mEffectComponentPtr;
	// 3段階目の通常攻撃状態のクラスのポインタ
	PlayerObjectStateThirdAttack* mThirdAttackPtr;
};