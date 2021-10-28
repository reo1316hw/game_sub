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

private:

	// 剣の初期回転値
	const Vector3 MSwordRot;
	// 剣の初期座標
	const Vector3 MSwordPos;

	// 武器メッシュ
	AttackMeshComponent* mWeaponMesh;
};