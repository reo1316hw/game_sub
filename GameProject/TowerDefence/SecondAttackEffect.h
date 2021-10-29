#pragma once

/// <summary>
/// プレイヤーの2段階目の通常攻撃エフェクト
/// </summary>
class SecondAttackEffect : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	/// <param name="_Scale"> 大きさ </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	/// <param name="_secondAttackPtr"> 2段階目の通常攻撃状態のクラスのポインタ </param>
	SecondAttackEffect(PlayerObject* _playerPtr, const Vector3& _Scale, const Tag& _ObjectTag, PlayerObjectStateSecondAttack* _secondAttackPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SecondAttackEffect() {};

	/// <summary>
	/// オブジェクトの更新処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	// 座標との差
	const float MOffset;

	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
	// エフェクトコンポーネントクラスのポインタ
	EffectComponent* mEffectComponentPtr;
	// 2段階目の通常攻撃状態のクラスのポインタ
	PlayerObjectStateSecondAttack* mSecondAttackPtr;
};