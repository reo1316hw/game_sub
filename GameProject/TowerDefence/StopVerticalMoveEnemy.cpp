#include "pch.h"

StopVerticalMoveEnemy::StopVerticalMoveEnemy(GameObject* _owner, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: GameObject(_ObjectTag, _SceneTag)
	, mEnemyOwner(_owner)
{
	// GameObjectメンバ変数の初期化
	mTag = _ObjectTag;

	// 武器の矩形当たり判定
	mBox = AABB(Vector3(-30.0f, -1.0f, 50.0f), Vector3(1.0f, 1.0f, 50.0f));
	mBoxColliderPtr = new BoxCollider(this, Tag::eStopVerticalMoveEnemy, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
}

void StopVerticalMoveEnemy::UpdateGameObject(float _deltaTime)
{
	mBox = mBoxColliderPtr->GetWorldBox();
	SetRotation(mEnemyOwner->GetRotation());
	SetPosition(mEnemyOwner->GetPosition());
}

void StopVerticalMoveEnemy::OnCollision(const GameObject& _HitObject)
{
}
