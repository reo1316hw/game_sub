#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �e�N���X�̃|�C���^ </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
EnemyAttackDecisionObject::EnemyAttackDecisionObject(GameObject* _owner, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, mOwner(_owner)
{
	// �ŏ��͍X�V�����Ȃ���Ԃɂ��ē����蔻����s��Ȃ��悤�ɂ���
	SetState(Dead);

	// ����̋�`�����蔻��
	mBox = AABB(Vector3(-50.0f, -50.0f, -90.0f), Vector3(50.0f, 50.0f, 15.0f));
	mBoxColliderPtr = new BoxCollider(this, Tag::eWeapon, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void EnemyAttackDecisionObject::UpdateGameObject(float _deltaTime)
{
	SetPosition(mOwner->GetPosition() + Vector3(0.0f, 50.0f,0.0f));
}

/// <summary>
/// �����蔻����s���悤�ɂ���
/// </summary>
void EnemyAttackDecisionObject::EnableCollision()
{
	SetState(Active);
}

/// <summary>
/// �����蔻����s��Ȃ��悤�ɂ���
/// </summary>
void EnemyAttackDecisionObject::DisableCollision()
{
	SetState(Dead);
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void EnemyAttackDecisionObject::OnCollision(const GameObject& _HitObject)
{
}