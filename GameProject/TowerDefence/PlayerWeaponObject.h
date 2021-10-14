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
	/// <param name="_owner"> 親クラスのポインタ </param>
	/// <param name="_skMesh"> 親クラスのスケルトンメッシュのポインタ </param>
	/// <param name="_GpmeshName"> gpmeshのパス </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	PlayerWeaponObject(GameObject* _owner, SkeletalMeshComponent* _skMesh, const std::string _GpmeshName, const Tag& _ObjectTag);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerWeaponObject() {};

	/// <summary>
	/// 攻撃用の当たり判定を追加
	/// </summary>
	/// <param name="_Scale"> 当たり判定の大きさ </param>
	void AddAttackHitBox(const float _Scale = 1.0f);


	/// <summary>
	/// 攻撃用の当たり判定を削除
	/// </summary>
	void RemoveAttackHitBox();

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

	// 剣の初期回転値
	const Vector3 MSwordRot;
	// 剣の初期座標
	const Vector3 MSwordPos;

	// 武器の矩形当たり判定
	AABB mWeaponBox;
	// 武器メッシュ
	AttackMeshComponent* mWeaponMesh;
};


