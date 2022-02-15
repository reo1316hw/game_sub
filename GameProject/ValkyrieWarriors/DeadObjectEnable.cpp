#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_bossActiveBoxPtr"> �X�V�����ĂȂ��I�u�W�F�N�g���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̊��N���X�̃|�C���^ </param>
/// <param name="_deadObjectPtr"> �X�V�����ĂȂ��I�u�W�F�N�g�̃|�C���^ </param>
DeadObjectEnable::DeadObjectEnable(GameObject* _owner, GameObject* _activeForObjectPtr, GameObject* _deadObjectPtr)
	: Component(_owner)
	, mActiveForObjectPtr(_activeForObjectPtr)
	, mDeadObjectPtr(_deadObjectPtr)
{
}

/// <summary>
/// �t���[�����̏���
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� < /param>
void DeadObjectEnable::Update(float _deltaTime)
{
	if (!mActiveForObjectPtr->GetIsEnable() || mDeadObjectPtr->GetState() == eActive)
	{
		return;
	}

	mDeadObjectPtr->SetState(eActive);
}