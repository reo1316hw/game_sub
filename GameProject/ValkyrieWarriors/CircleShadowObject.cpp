#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �e�N���X�̃|�C���^ </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
CircleShadowObject::CircleShadowObject(GameObject* _owner, const Vector3& _Scale, const std::string _GpmeshName, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MDistance(Vector3(0.0f, 0.0f, 2.0f))
	, mOwner(_owner)
{
	//GameObject�����o�ϐ��̏�����
	SetScale(_Scale);

	//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	mMeshComponentPtr = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	mMeshComponentPtr->SetMesh(RENDERER->GetMesh(_GpmeshName));
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void CircleShadowObject::UpdateGameObject(float _deltaTime)
{
	if (mOwner->GetState())
	{

	}

	mPosition = mOwner->GetPosition() + MDistance;
	SetPosition(mPosition);
}