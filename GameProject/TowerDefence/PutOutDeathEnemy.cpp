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
/// <param name="_enemyObjectList"> �G�l�~�[�̓��I�z�� </param>
/// <param name="_enemyObjectPtr"> �G�l�~�[�̃|�C���^�[ </param>
/// <returns> �X�V���ꂽ�G�l�~�[�̓��I�z�� </returns>
std::vector<EnemyObject*> PutOutDeathEnemy::PutOut(std::vector<EnemyObject*> _enemyObjectList, EnemyObject* _enemyObjectPtr)
{
	mEnemyObjectList = _enemyObjectList;
	mEnemyObjectPtr = _enemyObjectPtr;

	if (mEnemyObjectPtr->GetState() == State::eDead)
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