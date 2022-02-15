#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �e�N���X�̃|�C���^ </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
EnemyAttackDecisionObject::EnemyAttackDecisionObject(GameObject* _owner, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MCenterOffset(50.0f)
	, mOwner(_owner)
{
	// ����̋�`�����蔻��
	mBox = AABB(Vector3(-10.0f, -20.0f, 50.0f), Vector3(10.0f, 20.0f, 50.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
	// �ŏ��͓����蔻����s��Ȃ��悤�ɂ���
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void EnemyAttackDecisionObject::UpdateGameObject(float _deltaTime)
{	
	// ���S�̍��W����O�ɂ��炵�����W
	Vector3 offsetPos = mOwner->GetForward() * MCenterOffset;

	SetRotation(mOwner->GetRotation());
	mPosition = mOwner->GetPosition() + offsetPos;
	SetPosition(mPosition);
}