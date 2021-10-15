#pragma once

// 前方宣言
class AttackMeshComponent;

/// <summary>
/// プレイヤーステートの基底クラス
/// </summary>
class PlayerObjectStateBase
{
public:

	/// <summary>
    /// コンストラクタ
    /// </summary>
	PlayerObjectStateBase();

	/// <summary>
    /// デストラクタ
    /// </summary>
	virtual ~PlayerObjectStateBase() {};

	/// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="_owner"> プレイヤー(親)のポインタ </param>
    /// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
    /// <returns> プレイヤーの状態 </returns>
	virtual PlayerState Update(PlayerObject* _owner, const float _DeltaTime) = 0;

	/// <summary>
	/// 入力処理
	/// </summary>
	/// <param name="_owner"> プレイヤー(親)のポインタ </param>
	/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
	virtual void Input(PlayerObject* _owner, const InputState& _KeyState) {};

	/// <summary>
	/// プレイヤーの状態が変更して、最初に1回だけ呼び出される関数
	/// </summary>
	/// <param name="_owner"> プレイヤー(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	virtual void Enter(PlayerObject* _owner, const float _DeltaTime) = 0;

	/// <summary>
    /// プレイヤーの状態が変更して、最後に1回だけ呼び出される関数
    /// </summary>
    /// <param name="_owner"> プレイヤー(親)のポインタ </param>
    /// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	virtual void Exit(PlayerObject* _owner, const float _DeltaTime) {};

	/// <summary>
    /// ヒットした時の処理
    /// </summary>
    /// <param name="_owner"> プレイヤー(親)のポインタ </param>
    /// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
	virtual void OnCollision(PlayerObject* _owner, const GameObject& _HitObject) {};

protected:

	// 次のコンボにつなげるか
	bool mIsNextCombo;
	// 待機するか
	bool mIsIdle;
	// 走っているか
	bool mIsRun;
	// 全力疾走するか
	bool mIsSprint;
	// 攻撃するか
	bool mIsAttack;
	// 当たったか
	bool mIsHit;

	// gpSkelファイルの何番目のボーンか
	int	mAttackBoneIndex;

	// このステートに入ってからの経過時刻
	float mElapseTime;
	// アニメーション総時間
	float mTotalAnimTime;
	// キャラの現在のスピード
	float mCharaSpeed;

	//向き
	Vector3 mDirVec;
	//前進方向
	Vector3 mForwardVec;
	//右方向
	Vector3 mRightVec;
	// キャラの前進ベクトル
	Vector3 mCharaForwardVec;

	//武器メッシュのポインタ
	AttackMeshComponent* mAttackMeshComponent;

private:
};