#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_Pos"> ���W </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
BossBootSemitransparentWall::BossBootSemitransparentWall(const Vector3& _Pos, const Vector3& _Scale, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
{
	//GameObject�����o�ϐ��̏�����
	SetScale(_Scale);
	SetPosition(_Pos);

	// �����蔻��
	AABB box = AABB(Vector3(-2000.0f, -1.0f, -2000.0f), Vector3(2000.0f, 1.0f, 2000.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(box);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void BossBootSemitransparentWall::UpdateGameObject(float _deltaTime)
{
	mBox = mBoxColliderPtr->GetWorldBox();
}