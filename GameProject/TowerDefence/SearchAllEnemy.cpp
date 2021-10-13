#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SearchAllEnemy::SearchAllEnemy()
	: MDistanceThreshold(5000.0f)
	, mPutOutDeathEnemyPtr(nullptr)
	, mReferenceEnemyPos(Vector3::Zero)
{
	// ���S��Ԃ̃G�l�~�[��z�񂩂�o�����߂̃N���X�𐶐�
	mPutOutDeathEnemyPtr = new PutOutDeathEnemy();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SearchAllEnemy::~SearchAllEnemy()
{
	delete mPutOutDeathEnemyPtr;
}

/// <summary>
/// ��ƂȂ�G�l�~�[������
/// </summary>
/// <param name="_enemyObjectList"> �G�l�~�[�̓��I�z�� </param>
/// <returns> �X�V���ꂽ�G�l�~�[�̓��I�z�� </returns>
std::vector<EnemyObject*> SearchAllEnemy::Search(std::vector<EnemyObject*> _enemyObjectList)
{
	for (auto referenceEnemyItr : _enemyObjectList)
	{
		// ���S��Ԃ̃G�l�~�[��z�񂩂�o��
		mEnemyObjectList = mPutOutDeathEnemyPtr->PutOut(_enemyObjectList, referenceEnemyItr);
		// ��ƂȂ�G�l�~�[�̍��W
		mReferenceEnemyPos = referenceEnemyItr->GetPosition();
		// �ΏۂƂȂ�G�l�~�[������
		SearchTargetEnemy(_enemyObjectList, referenceEnemyItr);
	}

	return mEnemyObjectList;
}

/// <summary>
/// �ΏۂƂȂ�G�l�~�[������
/// </summary>
/// <param name="_enemyObjectList"> �G�l�~�[�̓��I�z�� </param>
/// <param name="_referenceEnemyItr"> ��ƂȂ�G�l�~�[ </param>
void SearchAllEnemy::SearchTargetEnemy(std::vector<EnemyObject*> _enemyObjectList, EnemyObject* _referenceEnemyItr)
{
	for (auto targetEnemyItr : _enemyObjectList)
	{
		if (targetEnemyItr == _referenceEnemyItr)
		{
			continue;
		}
		// �͈͓��ɐN�����Ă��������߂�
		InvadeWithinRange(_referenceEnemyItr, targetEnemyItr);
	}
}

/// <summary>
/// �͈͓��ɐN�����Ă��������߂�
/// </summary>
/// <param name="_referenceEnemyItr"> ��ƂȂ�G�l�~�[ </param>
/// <param name="_targetEnemyItr"> �ΏۂƂȂ�G�l�~�[ </param>
void SearchAllEnemy::InvadeWithinRange(EnemyObject* _referenceEnemyItr, EnemyObject* _targetEnemyItr)
{
	// �ΏۂƂȂ�G�l�~�[�̍��W
	Vector3 targetEnemyPos = _targetEnemyItr->GetPosition();
	// �G�l�~�[���m�̋���
	Vector3 distance = targetEnemyPos - mReferenceEnemyPos;

	if (distance.LengthSq() <= MDistanceThreshold)
	{
		distance.Normalize();
		_referenceEnemyItr->Separation(distance);
	}
}