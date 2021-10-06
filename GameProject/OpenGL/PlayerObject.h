#pragma once

// 前方宣言
class SkeletalMeshComponent;
class Animation;
class PlayerObjectStateBase;
class AttackMeshComponent;
class SphereCollider;

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
	/// <param name="_ObjectTag"> タグ </param>
	/// <param name="_SceneTag"> シーンタグ </param>
	PlayerObject(const Vector3& _Pos, const Vector3& _Scale, const char* _GpmeshName, const char* _GpskelName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

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
	/// ヒットされた時の処理
	/// </summary>
	/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
	void OnCollision(const GameObject& _HitObject)override;

	/// <summary>
	/// 武器がオブジェクトとヒットした時の処理
	/// </summary>
	/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
	void OnCollisionWeapon(const GameObject& _HitObject);

	// カメラ座標との差
	const Vector3 MCameraOffset;
	// 見たい座標との差
	const Vector3 MTargetOffset;
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

	// 見る対象のポジション
	Vector3 mTargetPos;
	// カメラのポジション
	Vector3 mCameraPos;

	// 現在のステート
	PlayerState mNowState;
	// 次のステート
	PlayerState mNextState;
	// 武器メッシュ
	AttackMeshComponent* mWeaponMesh;
	// ゲームオブジェクトのスケルトンメッシュ
	SkeletalMeshComponent* mSkeltalMeshComponentPtr;
	// 球状の当たり判定
	SphereCollider* mSphereCollider;

public:// ゲッターセッター

	/// <summary>
	/// Animationのポインタを取得
	/// </summary>
	/// <param name="_State"> プレイヤーの状態 </param>
	/// <returns> Animationのポインタ </returns>
	const Animation* GetAnimPtr(const PlayerState _State) const { return mAnimTypes[(int)_State]; };

	/// <summary>
	/// SkeletalMeshComponentのポインタを取得
	/// </summary>
	/// <returns> SkeletalMeshComponentのポインタ </returns>
	SkeletalMeshComponent* GetSkeletalMeshComponentPtr() { return mSkeltalMeshComponentPtr; };

	/// <summary>
	/// 見る対象のポジションを取得
	/// </summary>
	/// <returns> 見る対象のポジション </returns>
	Vector3 GetTargetPos() { return mTargetPos; };

	/// <summary>
	/// カメラのポジションを取得
	/// </summary>
	/// <returns> カメラのポジション </returns>
	Vector3 GetCameraPos() { return mCameraPos; };
};

