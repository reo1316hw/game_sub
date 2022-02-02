#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_enemyObjectManagerPtr"> �X�V���Ă���I�u�W�F�N�g���X�V�����Ȃ��悤�ɂ��邽�߂̃I�u�W�F�N�g�̊��N���X�̃|�C���^ </param>
ActiveObjectDisable::ActiveObjectDisable(GameObject* _owner, GameObject* _deadForObjectPtr)
	: Component(_owner)
	, mDeadForObjectPtr(_deadForObjectPtr)
{
}

/// <summary>
/// �t���[�����̏���
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� < /param>
void ActiveObjectDisable::Update(float _deltaTime)
{
	if (!mDeadForObjectPtr->GetIsDisable() || mOwner->GetState() == eDead)
	{
		return;
	}

	mOwner->SetState(eDead);
}