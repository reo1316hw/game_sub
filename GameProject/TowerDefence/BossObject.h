#pragma once

// 前方宣言
class SkeletalMeshComponent;
class BossObjectStateBase;
class BoxCollider;

/// <summary>
/// ボスの状態
/// </summary>
enum class BossState
{
	eBossStateWait = 0,             // 待機
	eBossStateTrack,                // 追跡
	eBossStateFrontAttack,          // 前方攻撃
	eBossStateAreaAttack,           // 範囲攻撃
	eBossStateOverheadAttack,    	// プレイヤーの頭上に攻撃
	eBossStateTeleportation,    	// 瞬間移動
	eBossStateDamage,               // ダメージを受けた
	eBossStateDeath,                // 死亡

	eBossStateNum,                  // 総アニメーション数
};

/// <summary>
/// ボス
/// </summary>
class BossObject : public GameObject
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
	BossObject(const Vector3& _Pos, const Vector3& _Scale, const std::string _GpmeshName, const char* _GpskelName,
		const Tag& _ObjectTag, PlayerObject* _playerPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BossObject() {};

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

	// 最大体力
	const int MMaxHp;
	// アニメーションの再生速度
	const float MPlayRate;
	// ヒットエフェクトの大きさ
	const Vector3 MHitEffectScale;

	// アニメーション可変長コンテナ
	std::vector<const Animation*>      mAnimTypes;
	// ステートクラスプール
	std::vector<BossObjectStateBase*> mStatePools;

	// 初期座標
	Vector3 mInitPosition;

	// 現在のステート
	BossState mNowState;
	// 次のステート
	BossState mNextState;

	//ゲームオブジェクトのスケルトンメッシュ
	SkeletalMeshComponent* mSkeltalMeshComponentPtr;

public://ゲッターセッター

	/// <summary>
	/// Animationのポインタを取得
	/// </summary>
	/// <param name="_State"> ボスの状態 </param>
	/// <returns> Animationのポインタ </returns>
	const Animation* GetAnimPtr(const BossState _State) const { return mAnimTypes[(int)_State]; }

	/// <summary>
	/// SkeletalMeshComponentのポインタを取得
	/// </summary>
	/// <returns> SkeletalMeshComponentのポインタ </returns>
	SkeletalMeshComponent* GetSkeletalMeshComponentPtr() { return mSkeltalMeshComponentPtr; }

	/// <summary>
	/// 初期座標を取得
	/// </summary>
	/// <returns> 初期座標 </returns>
	Vector3 GetInitPosition() { return mInitPosition; }
};

