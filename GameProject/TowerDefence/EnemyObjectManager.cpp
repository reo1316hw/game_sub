#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
EnemyObjectManager::EnemyObjectManager(const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
{
	// �G�l�~�[�����𐶐�����N���X�𐶐�
	mCreateEnemysPtr = new CreateEnemys(this);
	// �G�l�~�[�𐧌䂷��N���X�𐶐�
	new EnemyControler(this, mCreateEnemysPtr);
}