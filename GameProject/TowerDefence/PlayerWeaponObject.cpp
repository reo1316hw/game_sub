#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_skMesh"> 親クラスのスケルトンメッシュのポインタ </param>
/// <param name="_GpmeshName"> gpmeshのパス </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
PlayerWeaponObject::PlayerWeaponObject(SkeletalMeshComponent* _skMesh, const std::string _GpmeshName, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MSwordRot(Vector3(-Math::PiOver2 * 0.5f, Math::Pi * 0.9f, 0.0f))
	, MSwordPos(Vector3(-70.0f, -5.0f, 135.0f))
	, mWeaponMesh(nullptr)
{
	// 最初は更新させない状態にして当たり判定を行わないようにする
	SetState(Dead);

	// 武器のメッシュ
	mWeaponMesh = new AttackMeshComponent(this, _skMesh ,"index_01_r");
	mWeaponMesh->SetMesh(RENDERER->GetMesh(_GpmeshName));
	mWeaponMesh->SetOffsetRotation(MSwordRot);
	mWeaponMesh->SetOffsetPosition(MSwordPos);

	// 武器の矩形当たり判定
	mBox = AABB(Vector3(-2.0f, -0.0f, -90.0f), Vector3(2.0f, 10.0f, 15.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
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
/// 当たり判定を行なうようにする
/// </summary>
void PlayerWeaponObject::EnableCollision()
{
	SetState(Active);
}

/// <summary>
/// 当たり判定を行わないようにする
/// </summary>
void PlayerWeaponObject::DisableCollision()
{
	SetState(Dead);
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void PlayerWeaponObject::OnCollision(const GameObject& _HitObject)
{
}