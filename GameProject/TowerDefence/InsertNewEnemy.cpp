#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
InsertNewEnemy::InsertNewEnemy()
	: MMaxNumEnemysExist(1)
{
}

/// <summary>
/// �z��ɓ���鏈��
/// </summary>
/// <param name="_enemyObjectList"> �G�l�~�[�̓��I�z�� </param>
/// <param name="_enemyGeneratorList">�@�G�l�~�[������̓��I�z��@</param>
/// <returns> �X�V���ꂽ�G�l�~�[�̓��I�z�� </returns>
std::vector<EnemyObject*> InsertNewEnemy::Insert(std::vector<EnemyObject*> _enemyObjectList, std::vector<EnemyGenerator*> _enemyGeneratorList)
{
	if (_enemyObjectList.size() < MMaxNumEnemysExist)
	{
		for (auto itr : _enemyGeneratorList)
		{
			// �G�l�~�[�𐶐�
			EnemyObject* enemyObjectPtr = itr->CreateEnemyObject();
			_enemyObjectList.push_back(enemyObjectPtr);
		}
	}

	return _enemyObjectList;
}