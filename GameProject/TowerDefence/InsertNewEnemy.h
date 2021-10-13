#pragma once

/// <summary>
/// �V������������G�l�~�[��z��ɓ����
/// </summary>
class InsertNewEnemy
{
public:

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    InsertNewEnemy();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~InsertNewEnemy() {};

    /// <summary>
    /// �z��ɓ���鏈��
    /// </summary>
    /// <param name="_enemyObjectList"> �G�l�~�[�̓��I�z�� </param>
    /// <param name="_enemyGeneratorList">�@�G�l�~�[������̓��I�z��@</param>
    /// <returns> �X�V���ꂽ�G�l�~�[�̓��I�z�� </returns>
    std::vector<EnemyObject*> Insert(std::vector<EnemyObject*> _enemyObjectList, std::vector<EnemyGenerator*> _enemyGeneratorList);

private:

    // �G�l�~�[�����݂ł��鐔�̏��
    const unsigned int MMaxNumEnemysExist;
};