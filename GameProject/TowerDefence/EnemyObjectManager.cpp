#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
EnemyObjectManager::EnemyObjectManager(const Tag& _ObjectTag, PlayerObject* _playerPtr)
	: GameObject(_ObjectTag)
{
	// �G�l�~�[�����𐶐�����N���X�𐶐�
	mCreateEnemysPtr = new CreateEnemys(this);
	// �G�l�~�[�𐧌䂷��N���X�𐶐�
	mEnemysControlerPtr = new EnemysControler(this, mCreateEnemysPtr, _playerPtr);
}