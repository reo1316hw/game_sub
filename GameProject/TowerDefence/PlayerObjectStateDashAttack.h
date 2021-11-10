#pragma once

class DashAttackEffect;

/// <summary>
/// ダッシュ攻撃
/// </summary>
class PlayerObjectStateDashAttack : public PlayerObjectStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerObjectStateDashAttack();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerObjectStateDashAttack() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_owner"> プレイヤー(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	/// <returns> プレイヤーの状態 </returns>
	PlayerState Update(PlayerObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// 入力処理
	/// </summary>
	/// <param name="_owner"> プレイヤー(親)のポインタ </param>
	/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
	void Input(PlayerObject* _owner, const InputState& _KeyState)override;

	/// <summary>
	/// プレイヤーの状態が変更して、最初に1回だけ呼び出される関数
	/// </summary>
	/// <param name="_owner"> プレイヤー(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void Enter(PlayerObject* _owner, const float _DeltaTime)override;

	/// <summary>
    /// ヒットした時の処理
    /// </summary>
    /// <param name="_owner"> プレイヤー(親)のポインタ </param>
    /// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
	void OnCollision(PlayerObject* _owner, const GameObject& _HitObject)override;

private:

	// エネミーの攻撃のダメージ値
	const int MDamageValueEnemyAttack;
	// ヒットストップが終わるタイミング
	const int MHitStopEndTiming;
	// 当たり判定を有効にするタイミング
	const float MBoxEnableTiming;
	// 当たり判定を無効にするタイミング
	const float MBoxDisableTiming;
	// 攻撃時の速度
	const float MAttackSpeed;
	// アニメーションの再生速度
	const float MPlayRate;
	// コンボ有効フレーム
	const float MValidComboFrame;

	// 当たり判定の状態
	// true : 有効, false : 無効
	bool mIsCollisionState;
	// ヒットストップするか
	bool mIsHitStop;
	// 現在のステートに入って1回だけ当たり判定を有効にする
	bool mIsOneCollisionState;

	// ダメージ値
	int mDamageValue;
	// ヒットストップするフレーム数
	int mHitStopCount;

	// 座標
	Vector3 mPosition;
	// 速度
	Vector3 mVelocity;
	// 前方ベクトル
	Vector3 mForwardVec;

	// スケルトンクラスのポインタ
	SkeletalMeshComponent* skeletalMeshCompPtr;
	// ダッシュ攻撃エフェクトのクラスのポインタ
	DashAttackEffect* mDashAttackEffectPtr;

public:// ゲッターセッター

	/// <summary>
	/// 当たり判定の状態を取得
	/// </summary>
	/// <returns> 当たり判定の状態 </returns>
	bool GetIsCollisionState() { return mIsCollisionState; }

	/// <summary>
	/// ダッシュ攻撃エフェクトのクラスのポインタを設定
	/// </summary>
	/// <param name="_thirdAttackEffectPtr"> ダッシュ攻撃エフェクトのクラスのポインタ </param>
	void SetDashAttackEffectPtr(DashAttackEffect* _dashAttackEffectPtr) { mDashAttackEffectPtr = _dashAttackEffectPtr; }
};