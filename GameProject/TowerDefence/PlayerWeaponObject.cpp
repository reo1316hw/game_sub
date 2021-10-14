#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> 親クラスのポインタ </param>
/// <param name="_skMesh"> 親クラスのスケルトンメッシュのポインタ </param>
/// <param name="_GpmeshName"> gpmeshのパス </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
PlayerWeaponObject::PlayerWeaponObject(GameObject* _owner, SkeletalMeshComponent* _skMesh, const std::string _GpmeshName, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MSwordRot(Vector3(-Math::PiOver2 * 0.5f, Math::Pi * 0.9f, 0.0f))
	, MSwordPos(Vector3(-70.0f, -5.0f, 135.0f))
	, mWeaponBox(Vector3::Zero, Vector3::Zero)
	, mWeaponMesh(nullptr)
{
	// 武器のメッシュ
	mWeaponMesh = new AttackMeshComponent(this, _skMesh ,"index_01_r");
	mWeaponMesh->SetMesh(RENDERER->GetMesh(_GpmeshName));
	mWeaponMesh->SetOffsetRotation(MSwordRot);
	mWeaponMesh->SetOffsetPosition(MSwordPos);

	// 武器の矩形当たり判定
	mWeaponBox = AABB(Vector3(-2.0f, -0.0f, -90.0f), Vector3(2.0f, 10.0f, 15.0f));
}

/// <summary>
/// 攻撃用の当たり判定を追加
/// </summary>
/// <param name="_Scale"> 当たり判定の大きさ </param>
void PlayerWeaponObject::AddAttackHitBox(const float _Scale)
{
	mBoxColliderPtr = new BoxCollider(this, Tag::eWeapon, GetOnCollisionFunc());

	AABB box = mWeaponBox;
	box.m_min *= _Scale;
	box.m_max *= _Scale;

	mBoxColliderPtr->SetObjectBox(box);
}

/// <summary>
/// 攻撃用の当たり判定を削除
/// </summary>
void PlayerWeaponObject::RemoveAttackHitBox()
{
	if (mBoxColliderPtr)
	{
		delete mBoxColliderPtr;
		mBoxColliderPtr = nullptr;
	}
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void PlayerWeaponObject::UpdateGameObject(float _deltaTime)
{
	// 武器を振っているときの当たり判定の更新処理
	if (mBoxColliderPtr)
	{
		Matrix4 mat = mWeaponMesh->GetAttachTransMatrix();
		mBoxColliderPtr->SetForceTransForm(mat);
	}
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void PlayerWeaponObject::OnCollision(const GameObject& _HitObject)
{
}