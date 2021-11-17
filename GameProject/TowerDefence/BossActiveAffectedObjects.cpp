#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_bossActiveBoxPtr"> �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_bossBootSemitransparentWallPtr"> �{�X���N�����邱�Ƃɂ���ďo�����锼�����̕ǂ̃|�C���^ </param>
BossActiveAffectedObjects::BossActiveAffectedObjects(const Tag& _ObjectTag, BossActiveBox* _bossActiveBoxPtr,
	BossBootSemitransparentWall* _bossBootSemitransparentWallPtr)
	: GameObject(_ObjectTag)
{
	// �{�X���N�����邱�Ƃɂ���ďo�����锼�����̕ǂ�ON/OFF���s���R���|�[�l���g�𐶐�
	new BossBootSemitransparentWallSwitch(this, _bossActiveBoxPtr, _bossBootSemitransparentWallPtr);
}