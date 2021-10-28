#pragma once

class FirstAttackEffect;

/// <summary>
/// 3段階目の攻撃
/// </summary>
class PlayerObjectStateThirdAttack : public PlayerObjectStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerObjectStateThirdAttack();

	/// <summary>
    /// デストラクタ
    /// </summary>
	~PlayerObjectStateThirdAttack() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_owner"> プレイヤー(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	/// <returns> プレイヤーの状態 </returns>
	PlayerState Update(PlayerObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// プレイヤーの状態が変更して、最初に1回だけ呼び出される関数
	/// </summary>
	/// <param name="_owner"> プレイヤー(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void Enter(PlayerObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// プレイヤーの状態が変更して、最後に1回だけ呼び出される関数
	/// </summary>
	/// <param name="_owner"> プレイヤー(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void Exit(PlayerObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// ヒットした時の処理
	/// </summary>
	/// <param name="_owner"> プレイヤー(親)のポインタ </param>
	/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
	void OnCollision(PlayerObject* _owner, const GameObject& _HitObject)override;

private:

	// エネミーの攻撃のダメージ値
	const int MDamageValueEnemyAttack;
	// 当たり判定を有効にするタイミング
	const int MBoxEnableTiming;
	// ヒットストップが終わるタイミング
	const int MHitStopEndTiming;
	// 攻撃時の速度
	const float MAttackSpeed;
	// アニメーションの再生速度
	const float MPlayRate;

	// ヒットストップするか
	bool mIsHitStop;

	// ダメージ値
	int mDamageValue;
	// 当たり判定するまでのカウント
	int mHitUntilCount;
	// ヒットストップするフレーム数
	int mHitStopCount;

	// 座標
	Vector3 mPosition;
	// 前方ベクトル
	Vector3 mForwardVec;

	// スケルトンクラスのポインタ
	SkeletalMeshComponent* skeletalMeshCompPtr;
};