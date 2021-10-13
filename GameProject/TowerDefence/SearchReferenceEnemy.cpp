#include "pch.h"

SearchReferenceEnemy::SearchReferenceEnemy()
	: mPutOutDeathEnemyPtr(nullptr)
{
	mPutOutDeathEnemyPtr = new PutOutDeathEnemy();
}

SearchReferenceEnemy::~SearchReferenceEnemy()
{
	delete mPutOutDeathEnemyPtr;
}

/// <summary>
/// ��ƂȂ�G�l�~�[������
/// </summary>
/// <param name="_enemyList"> �G�l�~�[�̓��I�z�� </param>
std::vector<EnemyObject*> SearchReferenceEnemy::Search(std::vector<EnemyObject*> _enemyList)
{
	for (auto itr : _enemyList)
	{
		// ���S��Ԃ̃G�l�~�[��z�񂩂�o��
		/*_enemyList = */mPutOutDeathEnemyPtr->PutOut(_enemyList, itr);

		Vector3 position = itr->GetPosition();

		for (auto otherItr : _enemyList)
		{
			if (otherItr == itr)
			{
				continue;
			}

			Vector3 otherPosition = otherItr->GetPosition();

			Vector3 dis = otherPosition - position;

			if (dis.LengthSq() <= 5000.0f)
			{
				dis.Normalize();
				itr->Separation(dis);
			}
		}
	}

	return _enemyList;

	//if (mEnemyObjectList.size() < MMaxNumEnemysExist)
	//{
	//	for (auto itr : mEnemyGeneratorList)
	//	{
	//		// �G�l�~�[�𐶐�
	//		mEnemyObject = itr->CreateEnemyObject();
	//		mEnemyObjectList.push_back(mEnemyObject);
	//	}
	//}
}