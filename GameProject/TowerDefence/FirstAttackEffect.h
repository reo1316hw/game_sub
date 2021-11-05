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
	/// <param name="_Scale"> 大きさ </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	/// <param name="_firstAttackPtr"> 1段階目の通常攻撃状態のクラスのポインタ </param>
	FirstAttackEffect(PlayerObject* _playerPtr, const Vector3& _Scale, const Tag& _ObjectTag, PlayerObjectStateFirstAttack* _firstAttackPtr);

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
	/// ヒットした時の処理
	/// </summary>
	/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
	void OnCollision(const GameObject& _HitObject)override;

private:

	/// <summary>
	/// 攻撃が当たった時の処理
	/// </summary>
	/// <param name="_HitObject"> ヒットしたオブジェクト </param>
	/// <param name="_HitTag"> ヒットしたオブジェクトのタグ </param>
	void HitAttack(const GameObject& _HitObject, const Tag& _HitTag);

	// ヒットするオブジェクトのリスト
	Tag mHitTagList[2];

	// 座標との差
	const float MOffset;

	// 何体エネミーと当たっているかカウント
	int mHitEnemyCount;
	// ヒットする相手のリストの要素数
	int mHitTagListSize;

	// エネミーに向いたベクトル
	Vector3 mFaceInEnemyVec;
	// ヒットしたエネミーの群れの中心に向くベクトル
	Vector3 mFaceInFlockCenterVec;
	// ヒットしたオブジェクトのタグ
	Tag mHitTag;

	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
	// エフェクトコンポーネントクラスのポインタ
	EffectComponent* mEffectComponentPtr;
	// 1段階目の通常攻撃状態のクラスのポインタ
	PlayerObjectStateFirstAttack* mFirstAttackPtr;

public:// ゲッターセッター

	/// <summary>
	/// ヒットしたエネミーの群れの中心に向くベクトルを取得
	/// </summary>
	/// <returns> ヒットしたエネミーの群れの中心に向くベクトル </returns>
	Vector3 GetFaceInFlockCenterVec() { return mFaceInFlockCenterVec; }
};