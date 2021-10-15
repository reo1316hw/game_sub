#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> 親クラスのポインタ </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
EnemyAttackDecisionObject::EnemyAttackDecisionObject(GameObject* _owner, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MCenterOffset(50.0f)
	, mOwner(_owner)
{
	// 武器の矩形当たり判定
	mBox = AABB(Vector3(-10.0f, -30.0f, 50.0f), Vector3(10.0f, 30.0f, 50.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
	// 最初は当たり判定を行わないようにする
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void EnemyAttackDecisionObject::UpdateGameObject(float _deltaTime)
{	
	SetRotation(mOwner->GetRotation());
	mPosition = mOwner->GetPosition() + mOwner->GetForward() * MCenterOffset;
	SetPosition(mPosition);
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void EnemyAttackDecisionObject::OnCollision(const GameObject& _HitObject)
{
}