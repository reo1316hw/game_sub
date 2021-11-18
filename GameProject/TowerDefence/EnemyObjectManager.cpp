#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_enemyActiveBoxPtr"> �G�l�~�[���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_bossActiveBoxPtr"> �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
EnemyObjectManager::EnemyObjectManager(const Tag& _ObjectTag, DeadObjectActiveBox* _enemyActiveBoxPtr, DeadObjectActiveBox* _bossActiveBoxPtr)
	: GameObject(_ObjectTag)
{
	// �G�l�~�[�����𐶐�����N���X�𐶐�
	mCreateEnemysPtr = new CreateEnemys(this);
	// �G�l�~�[�𐧌䂷��N���X�𐶐�
	mEnemysControlerPtr = new EnemysControler(this, mCreateEnemysPtr, _enemyActiveBoxPtr, _bossActiveBoxPtr);
}