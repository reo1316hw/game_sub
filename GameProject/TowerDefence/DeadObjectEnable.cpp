#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_bossActiveBoxPtr"> �X�V�����ĂȂ��I�u�W�F�N�g���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_deadObjectPtr"> �X�V�����ĂȂ��I�u�W�F�N�g�̃|�C���^ </param>
DeadObjectEnable::DeadObjectEnable(GameObject* _owner, DeadObjectActiveBox* _deadObjectActiveBoxPtr, GameObject* _deadObjectPtr)
	: Component(_owner)
	, mDeadObjectActiveBoxPtr(_deadObjectActiveBoxPtr)
	, mDeadObjectPtr(_deadObjectPtr)
{
}

/// <summary>
/// �t���[�����̏���
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� < /param>
void DeadObjectEnable::Update(float _deltaTime)
{
	if (!mDeadObjectActiveBoxPtr->GetIsHitPlayer() || mDeadObjectPtr->GetState() == eActive)
	{
		return;
	}

	mDeadObjectPtr->SetState(eActive);
}