#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PutOutDeathEnemy::PutOutDeathEnemy()
	: mEnemyObjectPtr(nullptr)
{
}

/// <summary>
/// ���S��Ԃ̃G�l�~�[��z�񂩂�o��
/// </summary>
/// <param name="_enemyList"> �G�l�~�[�̓��I�z�� </param>
/// <param name="_enemyObjectPtr"> �G�l�~�[�̃|�C���^�[ </param>
std::vector<EnemyObject*> PutOutDeathEnemy::PutOut(std::vector<EnemyObject*> _enemyList, EnemyObject* _enemyObjectPtr)
{
	mEnemyObjectList = _enemyList;
	mEnemyObjectPtr = _enemyObjectPtr;

	if (mEnemyObjectPtr->GetState() == Dead)
	{
		// �z��̗v�f���폜
		RemoveEnemyObjectElements();
	}

	return mEnemyObjectList;
}

/// <summary>
/// �z��̗v�f���폜
/// </summary>
void PutOutDeathEnemy::RemoveEnemyObjectElements()
{
	auto iter = std::find(mEnemyObjectList.begin(), mEnemyObjectList.end(), mEnemyObjectPtr);
	if (iter != mEnemyObjectList.end())
	{
		std::iter_swap(iter, mEnemyObjectList.end() - 1);
		mEnemyObjectList.pop_back();
	}
}