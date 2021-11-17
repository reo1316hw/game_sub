#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_enemyActiveBoxPtr"> �G�l�~�[���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_enemyBootSemitransparentWallPtr"> �G�l�~�[���N�����邱�Ƃɂ���ďo�����锼�����̕ǂ̃|�C���^ </param>
EnemyActiveAffectedObjects::EnemyActiveAffectedObjects(const Tag& _ObjectTag, EnemyActiveBox* _enemyActiveBoxPtr,
	EnemyBootSemitransparentWall* _enemyBootSemitransparentWallPtr)
	: GameObject(_ObjectTag)
{
	// �G�l�~�[���N�����邱�Ƃɂ���ďo�����锼�����̕ǂ�ON/OFF���s���R���|�[�l���g�𐶐�
	new EnemyBootSemitransparentWallSwitch(this, _enemyActiveBoxPtr, _enemyBootSemitransparentWallPtr);
}