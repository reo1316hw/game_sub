#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_bossActiveBoxPtr"> �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_bossBootSemitransparentWallPtr"> �������̕ǂ̃|�C���^ </param>
SemitransparentWallEnabler::SemitransparentWallEnabler(const Tag& _ObjectTag, DeadObjectActiveBox* _deadObjectActiveBoxPtr,
	GameObject* _semitransparentWallPtr)
	: GameObject(_ObjectTag)
{
	// �{�X���N�����邱�Ƃɂ���ďo�����锼�����̕ǂ�L���ɂ���R���|�[�l���g�𐶐�
	new DeadObjectEnable(this, _deadObjectActiveBoxPtr, _semitransparentWallPtr);
}