#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_bossActiveBoxPtr"> �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_bossHitPointGaugePtr"> �{�X��hp�Q�[�W�̃|�C���^ </param>
/// <param name="_bossHitPointFramePtr"> �{�X��hp�̘g�̃|�C���^ </param>
BossHitPointUISwitch::BossHitPointUISwitch(GameObject* _owner, BossActiveBox* _bossActiveBoxPtr,
	BossHitPointGauge* _bossHitPointGaugePtr, BossHitPointFrame* _bossHitPointFramePtr)
	: Component(_owner)
	, mBossActiveBoxPtr(_bossActiveBoxPtr)
	, mBossHitPointGaugePtr(_bossHitPointGaugePtr)
	, mBossHitPointFramePtr(_bossHitPointFramePtr)
{
}

/// <summary>
/// �t���[�����̏���
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� < /param>
void BossHitPointUISwitch::Update(float _deltaTime)
{
	if (!mBossActiveBoxPtr->GetIsHitPlayer() || mBossHitPointGaugePtr->GetState() == eActive
		&& mBossHitPointFramePtr->GetState() == eActive)
	{
		return;
	}

	mBossHitPointGaugePtr->SetState(eActive);
	mBossHitPointFramePtr->SetState(eActive);
}