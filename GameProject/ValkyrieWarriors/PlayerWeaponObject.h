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
    /// <param name="_deathPtr"> 死亡状態のクラスのポインタ </param>
	PlayerWeaponObject(SkeletalMeshComponent* _skMesh, const std::string _GpmeshName, const Tag& _ObjectTag, PlayerObjectStateDeath* _deathPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerWeaponObject() {};

	/// <summary>
    /// オブジェクトの更新処理
    /// </summary>
    /// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	// 剣の初期回転値
	const Vector3 MSwordRot;
	// 剣の初期座標
	const Vector3 MSwordPos;

	// 武器メッシュ
	AttackMeshComponent* mWeaponMesh;
	// 死亡状態のクラスのポインタ
	PlayerObjectStateDeath* mDeathPtr;
};