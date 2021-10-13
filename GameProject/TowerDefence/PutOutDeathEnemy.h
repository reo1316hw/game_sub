#pragma once

/// <summary>
/// ���S��Ԃ̃G�l�~�[��z�񂩂�o�����߂̃N���X
/// </summary>
class PutOutDeathEnemy
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PutOutDeathEnemy();

	/// <summary>
    /// �f�X�g���N�^
    /// </summary>
	~PutOutDeathEnemy() {};

	/// <summary>
	/// ���S��Ԃ̃G�l�~�[��z�񂩂�o��
	/// </summary>
	/// <param name="_enemyObjectList"> �G�l�~�[�̓��I�z�� </param>
	/// <param name="_enemyObjectPtr"> �G�l�~�[�̃|�C���^�[ </param>
	/// <returns> �X�V���ꂽ�G�l�~�[�̓��I�z�� </returns>
	std::vector<EnemyObject*> PutOut(std::vector<EnemyObject*> _enemyObjectList, EnemyObject* _enemyObjectPtr);

private:

	/// <summary>
	/// �z��̗v�f���폜
	/// </summary>
	void RemoveEnemyObjectElements();

	// �G�l�~�[�̓��I�z��
	std::vector<EnemyObject*> mEnemyObjectList;

	// �G�l�~�[�̃|�C���^
	EnemyObject* mEnemyObjectPtr;
};
