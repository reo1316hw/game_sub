#pragma once

class PutOutDeathEnemy;

/// <summary>
/// ��ƂȂ�G�l�~�[���G�l�~�[�z�񂩂猟��
/// </summary>
class SearchReferenceEnemy
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SearchReferenceEnemy();
	
	/// <summary>
    /// �f�X�g���N�^
    /// </summary>
	~SearchReferenceEnemy();

	/// <summary>
    /// ��ƂȂ�G�l�~�[������
    /// </summary>
	/// <param name="_enemyList"> �G�l�~�[�̓��I�z�� </param>
	std::vector<EnemyObject*> Search(std::vector<EnemyObject*> _enemyList);

private:

	// ���S��Ԃ̃G�l�~�[��z�񂩂�o�����߂̃N���X�̃|�C���^
	PutOutDeathEnemy* mPutOutDeathEnemyPtr;
};

