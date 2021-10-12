#include "pch.h"

StopLateralMoveEnemy::StopLateralMoveEnemy(GameObject* _owner, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: GameObject(_ObjectTag, _SceneTag)
	, mEnemyOwner(_owner)
{
	// GameObject�����o�ϐ��̏�����
	mTag = _ObjectTag;

	// ����̋�`�����蔻��
	mBox = AABB(Vector3(-1.0f, -30.0f, 50.0f), Vector3(1.0f, 30.0f, 50.0f));
	mBoxColliderPtr = new BoxCollider(this, Tag::eStopLateralMoveEnemy, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
}

void StopLateralMoveEnemy::UpdateGameObject(float _deltaTime)
{
	mBox = mBoxColliderPtr->GetWorldBox();
	SetRotation(mEnemyOwner->GetRotation());
	SetPosition(mEnemyOwner->GetPosition());
}

void StopLateralMoveEnemy::OnCollision(const GameObject& _HitObject)
{
}
