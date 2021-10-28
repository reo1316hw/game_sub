#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_skMesh"> �e�N���X�̃X�P���g�����b�V���̃|�C���^ </param>
/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_deathPtr"> ���S��Ԃ̃N���X�̃|�C���^ </param>
PlayerWeaponObject::PlayerWeaponObject(SkeletalMeshComponent* _skMesh, const std::string _GpmeshName, const Tag& _ObjectTag, PlayerObjectStateDeath* _deathPtr)
	: GameObject(_ObjectTag)
	, MSwordRot(Vector3(-Math::PiOver2 * 0.5f, Math::Pi * 0.9f, 0.0f))
	, MSwordPos(Vector3(-70.0f, -5.0f, 135.0f))
	, mWeaponMesh(nullptr)
	, mDeathPtr(_deathPtr)
{
	// ����̃��b�V��
	mWeaponMesh = new AttackMeshComponent(this, _skMesh ,"index_01_r");
	mWeaponMesh->SetMesh(RENDERER->GetMesh(_GpmeshName));
	mWeaponMesh->SetOffsetRotation(MSwordRot);
	mWeaponMesh->SetOffsetPosition(MSwordPos);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void PlayerWeaponObject::UpdateGameObject(float _deltaTime)
{
	if (mDeathPtr->GetIsDead())
	{
		SetState(State::eDead);
	}
}