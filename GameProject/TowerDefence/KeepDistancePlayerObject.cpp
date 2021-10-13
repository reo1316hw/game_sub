#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> 親クラスのポインタ </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_SceneTag"> シーンのタグ</param>
KeepDistancePlayerObject::KeepDistancePlayerObject(GameObject* _owner, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: GameObject(_ObjectTag, _SceneTag)
	, mSphere(Vector3::Zero, 100.0f)
	, mOwner(_owner)
	//, mSphereColliderPtr(nullptr)
{
	// GameObjectメンバ変数の初期化
	mTag = _ObjectTag;
	SetScale(mOwner->GetScale());

	// 矩形当たり判定
	mBox = AABB(Vector3(-150.0f, -150.0f, 0.0f), Vector3(150.0f, 150.0f, 170.0f));

	// 矩形の当たり判定を行うコンポーネント
	mBoxColliderPtr = new BoxCollider(this, Tag::ePlayer, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);

	//// 球の当たり判定を行うコンポーネント
	//mSphereColliderPtr = new SphereCollider(this, _ObjectTag, GetOnCollisionFunc());
	//mSphereColliderPtr->SetObjectSphere(mSphere);
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void KeepDistancePlayerObject::UpdateGameObject(float _deltaTime)
{
	mBox = mBoxColliderPtr->GetWorldBox();
	SetPosition(mOwner->GetPosition());
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void KeepDistancePlayerObject::OnCollision(const GameObject& _HitObject)
{
}
