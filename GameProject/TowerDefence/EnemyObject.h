#pragma once

// 前方宣言
class SkeletalMeshComponent;
class EnemyObjectStateBase;
class BoxCollider;

/// <summary>
/// エネミーの状態
/// </summary>
enum class EnemyState
{
	eEnemyStateTrack = 0,       // 追跡
	eEnemyStateWait,            // 待機
	eEnemyStateAttack,          // 攻撃
	eEnemyStateLeftMove,        // 左移動
	eEnemyStateRightMove,        // 右移動
	eEnemyStateDamage,          // ダメージを受けた
	eEnemyStateDeath,           // 死亡

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
    /// <param name="_ObjectTag"> タグ </param>
    /// <param name="_SceneTag"> シーンタグ </param>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	EnemyObject(const Vector3& _Pos, const Vector3& _Scale, const std::string _GpmeshName, const char* _GpskelName,
		        const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, PlayerObject* _playerPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyObject() {};

	/// <summary>
	/// エネミー同士の引き離し
	/// </summary>
	/// <param name="_DirTargetEnemyVec"> 対象となるエネミーに向いたベクトル </param>
	void Separation(const Vector3& _DirTargetEnemyVec);

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

	// アニメーションの再生速度
	const float MPlayRate;

	// アニメーション可変長コンテナ
	std::vector<const Animation*>       mAnimTypes;
	// ステートクラスプール
	std::vector<EnemyObjectStateBase*> mStatePools;
	// 現在のステート
	EnemyState mNowState;
	// 次のステート
	EnemyState mNextState;
	//ゲームオブジェクトのスケルトンメッシュ
	SkeletalMeshComponent* mSkeltalMeshComponentPtr;

public://ゲッターセッター

	/// <summary>
	/// Animationのポインタを取得
	/// </summary>
	/// <param name="_State"> エネミーの状態 </param>
	/// <returns> Animationのポインタ </returns>
	const Animation* GetAnimPtr(const EnemyState _State) const { return mAnimTypes[(int)_State]; };

	/// <summary>
	/// SkeletalMeshComponentのポインタを取得
	/// </summary>
	/// <returns> SkeletalMeshComponentのポインタ </returns>
	SkeletalMeshComponent* GetSkeletalMeshComponentPtr() { return mSkeltalMeshComponentPtr; };
};

