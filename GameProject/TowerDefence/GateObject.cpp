#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_Pos"> ���W </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
GateObject::GateObject(const Vector3& _Pos, const Vector3& _Scale, const std::string _GpmeshName, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MRightGateDoorShiftVec(Vector3(-200.0f, 25.0f, 0.0f))
	, MLeftGateDoorShiftVec(Vector3(200.0f, 25.0f, 0.0f))
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

	// ��̉E���̍��W
	Vector3 rightGateDoorPos = _Pos + MLeftGateDoorShiftVec;
	// ��̉E���̑傫��
	Vector3 rightGateDoorScale = _Scale * Vector3(-1.0f, 1.0f, 1.0f);
	// ��̉E���𐶐�
	new GateDoorObject(rightGateDoorPos, rightGateDoorScale, "Assets/Model/Gate/GateDoor.gpmesh", Tag::eGateDoor);
	// ��̍����̍��W
	Vector3 leftGateDoorPos = _Pos + MRightGateDoorShiftVec;
	// ��̍����𐶐�
	new GateDoorObject(leftGateDoorPos, _Scale, "Assets/Model/Gate/GateDoor.gpmesh", Tag::eGateDoor);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void GateObject::UpdateGameObject(float _deltaTime)
{
	mBox = mBoxColliderPtr->GetWorldBox();
}