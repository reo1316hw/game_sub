#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_Pos"> ���W </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_AddAngle"> ��]�p�𑝂₷���߂̒萔 </param>
/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_enemysControlerPtr"> �G�l�~�[�𐧌䂷��R���|�[�l���g�N���X�̃|�C���^ </param>
GateDoorObject::GateDoorObject(const Vector3& _Pos, const Vector3& _Scale, const float _AddAngle,
	const std::string _GpmeshName, const Tag& _ObjectTag, EnemysControler* _enemysControlerPtr)
	: GameObject(_ObjectTag)
	, MAddAngle(_AddAngle)
	, mAngle(0.0f)
	, mEnemysControlerPtr(_enemysControlerPtr)
{
	//GameObject�����o�ϐ��̏�����
	SetScale(_Scale);
	SetPosition(_Pos);

	//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponentPtr = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponentPtr->SetMesh(RENDERER->GetMesh(_GpmeshName));

	// �����蔻��
	mMeshPtr = new Mesh;
	mMeshPtr = RENDERER->GetMesh(_GpmeshName);
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mMeshPtr->GetBox());
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void GateDoorObject::UpdateGameObject(float _deltaTime)
{
	mBox = mBoxColliderPtr->GetWorldBox();

	if (Math::Abs(mAngle) > 90.0f)
	{
		return;
	}

	if (mEnemysControlerPtr->GetDeadCount() >= 10)
	{
		mAngle += MAddAngle;

		// ��]����
		SelfRotation(Vector3::UnitZ, MAddAngle);
	}
}

/// <summary>
/// ��]����
/// </summary>
/// <param name="_Axis"> �� </param>
/// <param name="_Angle"> �p�x </param>
void GateDoorObject::SelfRotation(const Vector3& _Axis, const float& _Angle)
{
	float radian = Math::ToRadians(_Angle);
	Quaternion rot = mRotation;
	Quaternion inc(_Axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}