#pragma once

/// <summary>
/// 1段階目の攻撃
/// </summary>
class PlayerObjectStateFirstAttack : public PlayerObjectStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerObjectStateFirstAttack();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerObjectStateFirstAttack() {};

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

	// 当たり判定を有効にするタイミング
	const int MBoxEnableTiming;
	// 当たり判定を無効にするタイミング
	const int MBoxDisableTiming;
	// エネミーの攻撃のダメージ値
	const int MDamageValueEnemyAttack;
	// 攻撃時の速度
	const float MAttackSpeed;
	// アニメーションの再生速度
	const float MPlayRate;
	//移動するための左スティックのしきい値
	const float MLeftAxisThreshold;
	// コンボ有効フレーム
	const size_t MValidComboFrame;

	// 当たり判定の状態
	// true : 有効, false : 無効
	bool mIsCollisionState;

	// 回転するか
	bool mIsRotation;

	// ダメージ値
	int mDamageValue;
	// 当たり判定するまでのカウント
	int mHitUntilCount;

	// フレーム数
	size_t mNumFrame;

	// 左スティックの入力値(-1~1)
	Vector2 mleftAxis;
	// 座標
	Vector3 mPosition;
	// 前方ベクトル
	Vector3 mForwardVec;

public:// ゲッターセッター

	/// <summary>
	/// 当たり判定の状態を取得
	/// </summary>
	/// <returns> 当たり判定の状態 </returns>
	bool GetIsCollisionState() { return mIsCollisionState; }
};