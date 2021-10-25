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
	, MEnableIsHitTiming(120)
	, MSwordRot(Vector3(-Math::PiOver2 * 0.5f, Math::Pi * 0.9f, 0.0f))
	, MSwordPos(Vector3(-70.0f, -5.0f, 135.0f))
	, mIsHitDisableCount(0)
	, mIsHit(false)
	, mDisableIsHit(false)
	, mWeaponMesh(nullptr)
	, mPlayerPtr(_playerPtr)
{
	// 武器のメッシュ
	mWeaponMesh = new AttackMeshComponent(this, _skMesh ,"index_01_r");
	mWeaponMesh->SetMesh(RENDERER->GetMesh(_GpmeshName));
	mWeaponMesh->SetOffsetRotation(MSwordRot);
	mWeaponMesh->SetOffsetPosition(MSwordPos);

	// 武器の矩形当たり判定
	mBox = AABB(Vector3(-2.0f, -0.0f, -90.0f), Vector3(2.0f, 10.0f, 15.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
	// 最初は当たり判定を行わないようにする
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);
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

	// ヒットストップ時にオブジェクトと常に当たってしまうので、ヒットフラグを一定時間無効にする
	if (mDisableIsHit)
	{
		mIsHit = false;
		++mIsHitDisableCount;

		if (mIsHitDisableCount >= MEnableIsHitTiming)
		{
			mIsHitDisableCount = 0;
			mDisableIsHit = false;
		}
	}
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void PlayerWeaponObject::OnCollision(const GameObject& _HitObject)
{
	// オブジェクトのタグ
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eEnemy && !mDisableIsHit && mPlayerPtr->GetPlayerState() == PlayerState::ePlayerStateThirdAttack)
	{
  		mIsHit = true;
	    mDisableIsHit = true;
	}
}