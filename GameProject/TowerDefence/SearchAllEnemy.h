#pragma once

// �O���錾
class PutOutDeathEnemy;

/// <summary>
/// �S�ẴG�l�~�[���G�l�~�[�z�񂩂猟��
/// </summary>
class SearchAllEnemy
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SearchAllEnemy();
	
	/// <summary>
    /// �f�X�g���N�^
    /// </summary>
	~SearchAllEnemy();

	/// <summary>
    /// �S�ẴG�l�~�[������
    /// </summary>
	/// <param name="_enemyObjectList"> �G�l�~�[�̓��I�z�� </param>
	/// <returns> �X�V���ꂽ�G�l�~�[�̓��I�z�� </returns>
	std::vector<EnemyObject*> Search(std::vector<EnemyObject*> _enemyObjectList);

private:

	/// <summary>
	/// �ΏۂƂȂ�G�l�~�[������
	/// </summary>
	/// <param name="_enemyObjectList"> �G�l�~�[�̓��I�z�� </param>
	/// <param name="_referenceEnemyItr"> ��ƂȂ�G�l�~�[ </param>
	void SearchTargetEnemy(std::vector<EnemyObject*> _enemyObjectList, EnemyObject* _referenceEnemyItr);

	/// <summary>
	/// �͈͓��ɐN�����Ă��������߂�
	/// </summary>
	/// <param name="_referenceEnemyItr"> ��ƂȂ�G�l�~�[ </param>
	/// <param name="_targetEnemyItr"> �ΏۂƂȂ�G�l�~�[ </param>
	void InvadeWithinRange(EnemyObject* _referenceEnemyItr, EnemyObject* _targetEnemyItr);

	// �����̂������l
	const float MDistanceThreshold;

	// �G�l�~�[�̓��I�z��
	std::vector<EnemyObject*> mEnemyObjectList;

	// ��ƂȂ�G�l�~�[�̍��W
	Vector3 mReferenceEnemyPos;

	// ���S��Ԃ̃G�l�~�[��z�񂩂�o�����߂̃N���X�̃|�C���^
	PutOutDeathEnemy* mPutOutDeathEnemyPtr;
};

