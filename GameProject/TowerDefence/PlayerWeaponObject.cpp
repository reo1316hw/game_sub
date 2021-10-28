#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_skMesh"> 親クラスのスケルトンメッシュのポインタ </param>
/// <param name="_GpmeshName"> gpmeshのパス </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
PlayerWeaponObject::PlayerWeaponObject(SkeletalMeshComponent* _skMesh, const std::string _GpmeshName, const Tag& _ObjectTag, PlayerObject* _playerPtr)
	: GameObject(_ObjectTag)
	, MSwordRot(Vector3(-Math::PiOver2 * 0.5f, Math::Pi * 0.9f, 0.0f))
	, MSwordPos(Vector3(-70.0f, -5.0f, 135.0f))
	, mWeaponMesh(nullptr)
{
	// 武器のメッシュ
	mWeaponMesh = new AttackMeshComponent(this, _skMesh ,"index_01_r");
	mWeaponMesh->SetMesh(RENDERER->GetMesh(_GpmeshName));
	mWeaponMesh->SetOffsetRotation(MSwordRot);
	mWeaponMesh->SetOffsetPosition(MSwordPos);
}