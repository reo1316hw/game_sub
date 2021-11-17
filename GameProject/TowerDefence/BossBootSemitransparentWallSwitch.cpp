#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_bossActiveBoxPtr"> �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_bossBootSemitransparentWallPtr"> �{�X���N�����邱�Ƃɂ���ďo�����锼�����̕ǂ̃|�C���^ </param>
BossBootSemitransparentWallSwitch::BossBootSemitransparentWallSwitch(GameObject* _owner, BossActiveBox* _bossActiveBoxPtr,
	BossBootSemitransparentWall* _bossBootSemitransparentWallPtr)
	: Component(_owner)
	, mBossActiveBoxPtr(_bossActiveBoxPtr)
	, mBossBootSemitransparentWallPtr(_bossBootSemitransparentWallPtr)
{
}

/// <summary>
/// �t���[�����̏���
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� < /param>
void BossBootSemitransparentWallSwitch::Update(float _deltaTime)
{
	if (!mBossActiveBoxPtr->GetIsHitPlayer() || mBossBootSemitransparentWallPtr->GetState() == eActive)
	{
		return;
	}

	mBossBootSemitransparentWallPtr->SetState(eActive);
}