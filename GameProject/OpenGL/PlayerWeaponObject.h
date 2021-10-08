#pragma once

/// <summary>
/// プレイヤーの武器
/// </summary>
class PlayerWeaponObject : public GameObject
{
public:

	PlayerWeaponObject(GameObject* _owner, SkeletalMeshComponent* _skMesh, const std::string _GpmeshName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	~PlayerWeaponObject() {};

	void AddAttackHitSphere(const float _Scale = 1.0f);
	void RemoveAttackHitSphere();

	void UpdateGameObject(float _deltaTime)override;

private:

	void OnCollision(const GameObject& _hitObject)override;

	// 剣の初期回転値
	const Vector3 MSwordRot;
	// 剣の初期座標
	const Vector3 MSwordPos;

	// 武器の球状当たり判定
	Sphere mWeaponSphere;
	// アタッチされているオブジェクト
	GameObject* mOwner;
	// 武器メッシュ
	AttackMeshComponent* mWeaponMesh;
	// 球の当たり判定を行うコンポーネントのポインタ
	SphereCollider* mSphereCollider;
};


