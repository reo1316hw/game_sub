#pragma once

// 前方宣言
class SkeletalMeshComponent;
class EnemyObjectStateBase;
class EnemyAttackDecisionObject;
class EnemyHitPointGauge;
class EnemyHitPointFrame;
class BoxCollider;

/// <summary>
/// エネミーの状態
/// </summary>
enum class EnemyState
{
	eEnemyStateTrack = 0,        // 追跡
	eEnemyStateWait,             // 待機
	eEnemyStateAttack,           // 攻撃
	eEnemyStateAttackReady,      // 攻撃準備
	eEnemyStateLeftMove,         // 左移動
	eEnemyStateRightMove,        // 右移動
	eEnemyStateImpactDamage,     // ダメージを受けた(小さい衝撃)
	eEnemyStateSweepFallDamage,  // ダメージを受けた(吹っ飛んで落ちる)
	eEnemyStateFlyingBackDamage, // ダメージを受けた(遠くまで飛行して落ちる)
	eEnemyStateStandUp,          // 起き上がり
	eEnemyStateFallingBackDeath, // 死亡(その場で崩れ落ちる)
	eEnemyStateSweepFallDeath,   // 死亡(吹っ飛んで落ちる)
	eEnemyStateFlyingBackDeath,  // 死亡(遠くまで飛行して落ちる)

	eEnemyStateNum,             // 総アニメーション数
};

/// <summary>
/// エネミー
/// </summary>
class EnemyObject : public GameObject
{
public:

	/// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="_Pos"> 座標 </param>
    /// <param name="_Scale"> 大きさ </param>
    /// <param name="_GpmeshName"> gpmeshのパス </param>
    /// <param name="_GpskelName"> gpskelのパス </param>
    /// <param name="_ObjectTag"> オブジェクトのタグ </param>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	EnemyObject(const Vector3& _Pos, const Vector3& _Scale, const std::string _GpmeshName, const char* _GpskelName,
		        const Tag& _ObjectTag, PlayerObject* _playerPtr);

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_ShouldTutorialUse"> チュートリアルで使用するか </param>
	/// <param name="_Pos"> 座標 </param>
	/// <param name="_Scale"> 大きさ </param>
	/// <param name="_GpmeshName"> gpmeshのパス </param>
	/// <param name="_GpskelName"> gpskelのパス </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	EnemyObject(const bool& _ShouldTutorialUse, const Vector3& _Pos, const Vector3& _Scale, const std::string _GpmeshName,
		const char* _GpskelName, const Tag& _ObjectTag, PlayerObject* _playerPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyObject() {};

	/// <summary>
	/// エネミー同士の引き離し
	/// </summary>
	/// <param name="_DirTargetEnemyVec"> 対象となるエネミーに向いたベクトル </param>
	void Separation(const Vector3& _DirTargetEnemyVec)override;

	/// <summary>
    /// オブジェクトの更新処理
    /// </summary>
    /// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	/// <summary>
    /// ヒットした時の処理
    /// </summary>
    /// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
	void OnCollision(const GameObject& _HitObject)override;

	// チュートリアルで使用するか
	const bool MShouldTutorialUse;
	
	// 最大体力
	const int MMaxHp;

	// アニメーションの再生速度
	const float MPlayRate;

	// hpゲージの大きさ
	const Vector3 MHpGaugeScale;
	// ヒットエフェクトの大きさ
	const Vector3 MHitEffectScale;

	// アニメーション可変長コンテナ
	std::vector<const Animation*>       mAnimTypes;
	// ステートクラスプール
	std::vector<EnemyObjectStateBase*> mStatePools;

	// 初期座標
	Vector3 mInitPosition;

	// 現在のステート
	EnemyState mNowState;
	// 次のステート
	EnemyState mNextState;

	//ゲームオブジェクトのスケルトンメッシュ
	SkeletalMeshComponent* mSkeltalMeshComponentPtr;
	// エネミーの攻撃判定オブジェクトのポインタ
	EnemyAttackDecisionObject* mEnemyAttackPtr;
	// エネミーのhpゲージのポインタ
	EnemyHitPointGauge* mEnemyHitPointGaugePtr;
	// エネミーのhpの枠のポインタ
	EnemyHitPointFrame* mEnemyHitPointFramePtr;

public://ゲッターセッター

	/// <summary>
	/// チュートリアルで使用するかフラグを取得
	/// </summary>
	/// <returns> チュートリアルで使用するかフラグ </returns>
	const bool GetShouldTutorialUse() const { return MShouldTutorialUse; }

	/// <summary>
	/// Animationのポインタを取得
	/// </summary>
	/// <param name="_State"> エネミーの状態 </param>
	/// <returns> Animationのポインタ </returns>
	const Animation* GetAnimPtr(const EnemyState _State) const { return mAnimTypes[(int)_State]; }

	/// <summary>
	/// SkeletalMeshComponentのポインタを取得
	/// </summary>
	/// <returns> SkeletalMeshComponentのポインタ </returns>
	SkeletalMeshComponent* GetSkeletalMeshComponentPtr() { return mSkeltalMeshComponentPtr; }

	/// <summary>
	/// エネミーの現在のステートを取得
	/// </summary>
	/// <returns> エネミーの現在のステート </returns>
	EnemyState GetEnemyState() { return mNowState; }

	/// <summary>
	/// 初期座標を取得
	/// </summary>
	/// <returns> 初期座標 </returns>
	Vector3 GetInitPosition() { return mInitPosition; }

	/// <summary>
	/// エネミーのhpゲージのポインタ
	/// </summary>
	/// <returns> エネミーのhpゲージ </returns>
	EnemyHitPointGauge* GetEnemyHitPointGaugePtr() {return mEnemyHitPointGaugePtr; }

	/// <summary>
	/// エネミーのhpの枠のポインタ
	/// </summary>
	/// <returns> エネミーのhpの枠 </returns>
	EnemyHitPointFrame* GetEnemyHitPointFramePtr() { return mEnemyHitPointFramePtr; }

};

