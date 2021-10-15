#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> 親クラスのポインタ </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
EnemyAttackDecisionObject::EnemyAttackDecisionObject(GameObject* _owner, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, mOwner(_owner)
{
	// 最初は更新させない状態にして当たり判定を行わないようにする
	SetState(Dead);

	// 武器の矩形当たり判定
	mBox = AABB(Vector3(-50.0f, -50.0f, -90.0f), Vector3(50.0f, 50.0f, 15.0f));
	mBoxColliderPtr = new BoxCollider(this, Tag::eWeapon, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void EnemyAttackDecisionObject::UpdateGameObject(float _deltaTime)
{
	SetPosition(mOwner->GetPosition() + Vector3(0.0f, 50.0f,0.0f));
}

/// <summary>
/// 当たり判定を行うようにする
/// </summary>
void EnemyAttackDecisionObject::EnableCollision()
{
	SetState(Active);
}

/// <summary>
/// 当たり判定を行わないようにする
/// </summary>
void EnemyAttackDecisionObject::DisableCollision()
{
	SetState(Dead);
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void EnemyAttackDecisionObject::OnCollision(const GameObject& _HitObject)
{
}