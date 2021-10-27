#pragma once

// 前方宣言
class SkeletalMeshComponent;
class Animation;
class PlayerObjectStateBase;
class AttackMeshComponent;
class SphereCollider;
class PlayerWeaponObject;
class MainCameraObject;
class PlayerObjectStateRunLoop;
class PlayerObjectStateSprintStart;
class PlayerObjectStateSprintLoop;

/// <summary>
/// プレイヤーの状態
/// </summary>
enum class PlayerState
{
	ePlayerStateIdle = 0,		// 待機
	ePlayerStateRunLoop,		// 走っている
	ePlayerStateSprintStart,	// 全力疾走始め
	ePlayerStateSprintLoop,		// 全力疾走している
	ePlayerStateFirstAttack,	// 1段階目の通常攻撃
	ePlayerStateSecondAttack,	// 2段階目の通常攻撃
	ePlayerStateThirdAttack,	// 3段階目の通常攻撃
	ePlayerStateDashAttack,     // ダッシュ攻撃
	ePlayerStateDamage,         // ダメージを受けた
	ePlayerStateDeath,          // 死亡状態

	ePlayerStateNum,            // 総アニメーション数
};

/// <summary>
/// プレイヤー
/// </summary>
class PlayerObject : public GameObject
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
	PlayerObject(const Vector3& _Pos, const Vector3& _Scale, const char* _GpmeshName, const char* _GpskelName, const Tag& _ObjectTag);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerObject() {};

	/// <summary>
	/// オブジェクトの更新処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

	/// <summary>
	/// 入力を引数で受け取る更新関数
	/// 基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
	/// </summary>
	/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
	void GameObjectInput(const InputState& _KeyState)override;

private:

	/// <summary>
	/// 回転処理
	/// </summary>
	/// <param name="_Axis"> 軸 </param>
	/// <param name="_Angle"> 角度 </param>
	void SelfRotation(const Vector3 _Axis, const float _Angle);

	/// <summary>
	/// ヒットした時の処理
	/// </summary>
	/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
	void OnCollision(const GameObject& _HitObject)override;

	// 最大体力
	const int MMaxHp;
	// 剣の初期回転値
	const Vector3 MSwordRot;
	// 剣の初期座標
	const Vector3 MSwordPos;
	// アニメーションの再生速度
	const float MPlayRate;
	// 角度
	const float MAngle;

	// アニメーション可変長コンテナ
	std::vector<const Animation*>       mAnimTypes;
	// ステートクラスプール
	std::vector<PlayerObjectStateBase*> mStatePools;

	// 現在のステート
	PlayerState mNowState;
	// 次のステート
	PlayerState mNextState;
	// スケルトンメッシュのポインタ
	SkeletalMeshComponent* mSkeltalMeshComponentPtr;
	// プレイヤー武器のポインタ
	PlayerWeaponObject* mWeaponPtr;
	// カメラのポインタ
	MainCameraObject* mMainCameraPtr;
	// 走り状態のクラスのポインタ
	PlayerObjectStateRunLoop* mRunLoopPtr;
	// 全力疾走始め状態のクラスのポインタ
	PlayerObjectStateSprintStart* mSprintStartPtr;
	// 全力疾走状態のクラスのポインタ
	PlayerObjectStateSprintLoop* mSprintLoopPtr;

public:// ゲッターセッター

	/// <summary>
	/// Animationのポインタを取得
	/// </summary>
	/// <param name="_State"> プレイヤーの状態 </param>
	/// <returns> Animationのポインタ </returns>
	const Animation* GetAnimPtr(const PlayerState _State) const { return mAnimTypes[(int)_State]; }

	/// <summary>
	/// スケルトンメッシュのポインタを取得
	/// </summary>
	/// <returns> スケルトンメッシュのポインタ </returns>
	SkeletalMeshComponent* GetSkeletalMeshComponentPtr() { return mSkeltalMeshComponentPtr; }

	/// <summary>
	/// 現在のステートを取得
	/// </summary>
	/// <returns> 現在のステート </returns>
	PlayerState GetPlayerState() { return mNowState; }

	/// <summary>
	/// カメラのポインタを設定
	/// </summary>
	/// <param name="_mainCameraPtr"> カメラのポインタ </param>
	void SetMainCameraPtr(MainCameraObject* _mainCameraPtr);
};

