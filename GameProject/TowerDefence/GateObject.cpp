#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_Pos"> ���W </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_OpenToEnemyDefeatNum"> ����J�����߂ɓ|���G�l�~�[�̐� </param>
/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_enemysControlerPtr"> �G�l�~�[�𐧌䂷��R���|�[�l���g�N���X�̃|�C���^ </param>
GateObject::GateObject(const Vector3& _Pos, const Vector3& _Scale, const int& _OpenToDefeatEnemyNum,
	const std::string _GpmeshName, const Tag& _ObjectTag, EnemysControler* _enemysControlerPtr)
	: GameObject(_ObjectTag)
	, BoxColliderNum(2)
	, MRightGateDoorAddAngle(0.5f)
	, MLeftGateDoorAddAngle(-0.5f)
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

	for (int i = 0; i < BoxColliderNum; i++)
	{
		// ��`�����蔻��𒚓x�悢�ʒu�ɂ��炷���߂̃x�N�g��
		Vector3 BoxColliderShiftVec = Vector3(550.0f, 0.0f, 0.0f) * i;
		// ��`�����蔻��̍ŏ��̃|�W�V����
		Vector3 BoxColliderMin = Vector3(-350.0f, 0.0f, 0.0f) + BoxColliderShiftVec;
		// ��`�����蔻��̍ő�̃|�W�V����
		Vector3 BoxColliderMax = Vector3(-200.0f, 60.0f, 800.0f) + BoxColliderShiftVec;

		// �����蔻��
		AABB box = AABB(BoxColliderMin, BoxColliderMax);
		mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
		mBoxColliderPtr->SetObjectBox(box);
	}
	
	// ��̉E���̍��W
	Vector3 rightGateDoorPos = _Pos + MLeftGateDoorShiftVec;
	// ��̉E���̑傫��
	Vector3 rightGateDoorScale = _Scale * Vector3(-1.0f, 1.0f, 1.0f);
	// ��̉E���𐶐�
	new GateDoorObject(rightGateDoorPos, rightGateDoorScale, MRightGateDoorAddAngle, _OpenToDefeatEnemyNum,
		               "Assets/Model/Gate/GateDoor.gpmesh", Tag::eGateDoor, _enemysControlerPtr);
	// ��̍����̍��W
	Vector3 leftGateDoorPos = _Pos + MRightGateDoorShiftVec;
	// ��̍����𐶐�
	new GateDoorObject(leftGateDoorPos, _Scale, MLeftGateDoorAddAngle, _OpenToDefeatEnemyNum,
		               "Assets/Model/Gate/GateDoor.gpmesh", Tag::eGateDoor, _enemysControlerPtr);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void GateObject::UpdateGameObject(float _deltaTime)
{
	mBox = mBoxColliderPtr->GetWorldBox();
}