#pragma once

/// <summary>
/// プレイヤーの武器
/// </summary>
class PlayerWeaponObject : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_skMesh"> 親クラスのスケルトンメッシュのポインタ </param>
	/// <param name="_GpmeshName"> gpmeshのパス </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
    /// <param name="_playerPtr"> プレイヤーのポインタ </param>
	PlayerWeaponObject(SkeletalMeshComponent* _skMesh, const std::string _GpmeshName, const Tag& _ObjectTag, PlayerObject* _playerPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerWeaponObject() {};

	/// <summary>
	/// オブジェクトの更新処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

	/// <summary>
    /// ヒットしたか確認
    /// </summary>
    /// <returns> ヒットしたか </returns>
	bool IsHitCheck() { return mIsHit == true; }

private:

	/// <summary>
    /// ヒットした時の処理
    /// </summary>
    /// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
	void OnCollision(const GameObject& _HitObject)override;

	// ヒットフラグを有効にするタイミング
	const int MEnableIsHitTiming;
	// 剣の初期回転値
	const Vector3 MSwordRot;
	// 剣の初期座標
	const Vector3 MSwordPos;

	// ヒットしたか
	bool mIsHit;
	// ヒットフラグを無効にするフラグ
	bool mDisableIsHit;

	// ヒットフラグを無効時間
	int mIsHitDisableCount;

	// 武器メッシュ
	AttackMeshComponent* mWeaponMesh;
	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
};