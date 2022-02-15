#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_Pos"> ���W </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_AddAngle"> ��]�p�𑝂₷���߂̒萔 </param>
/// <param name="_OpenToEnemyDefeatNum"> ����J�����߂ɓ|���G�l�~�[�̐� </param>
/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_enemysControlerPtr"> �G�l�~�[�𐧌䂷��R���|�[�l���g�N���X�̃|�C���^ </param>
GateDoorObject::GateDoorObject(const Vector3& _Pos, const Vector3& _Scale, const float _AddAngle, const int& _OpenToDefeatEnemyNum,
	const std::string _GpmeshName, const Tag& _ObjectTag, EnemysControler* _enemysControlerPtr)
	: GameObject(_ObjectTag)
	, MAddAngle(_AddAngle)
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

	// ���g����]���鏈��
	SelfRotation* selfRotationPtr = new SelfRotation(this, Vector3::UnitZ, 0.0f);
	// ����J������
	mOpenGatePtr = new OpenGate(this, Vector3::UnitZ, MAddAngle, _OpenToDefeatEnemyNum, _enemysControlerPtr, selfRotationPtr);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void GateDoorObject::UpdateGameObject(float _deltaTime)
{
	mBox = mBoxColliderPtr->GetWorldBox();
}