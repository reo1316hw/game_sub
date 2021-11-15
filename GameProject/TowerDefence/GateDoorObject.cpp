#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_Pos"> ���W </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
GateDoorObject::GateDoorObject(const Vector3& _Pos, const Vector3& _Scale,
	const std::string _GpmeshName, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
{
	//GameObject�����o�ϐ��̏�����
	SetScale(_Scale);
	SetPosition(_Pos);

	//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponentPtr = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponentPtr->SetMesh(RENDERER->GetMesh(_GpmeshName));

	//// ��]����
	//SelfRotation(Vector3::UnitZ, _Angle);
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