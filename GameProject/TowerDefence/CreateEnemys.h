#pragma once

// �O���錾
class EnemyGenerator;
class EnemyObject;

/// <summary>
/// �G�l�~�[�̐���
/// </summary>
class CreateEnemys : public Component
{
public:

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
    CreateEnemys(GameObject* _owner);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~CreateEnemys() {};

    /// <summary>
    /// �G�l�~�[������𐶐�
    /// </summary>
    /// <param name="_Pos"> ���W </param>
    /// <param name="_Scale"> �傫�� </param>
    /// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
    void CreateEnemyGenerator(const Vector3& _Pos, const Vector3& _Scale, PlayerObject* _playerPtr);

    /// <summary>
    /// �G�l�~�[�𐶐�
    /// </summary>
    /// <param name="_GpmeshName"> gpmesh�̃p�X </param>
    /// <param name="_GpskelName"> gpskel�̃p�X </param>
    /// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
    /// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
    void CreateEnemyObject(const char* _GpmeshName, const char* _GpskelName, const Tag& _ObjectTag, PlayerObject* _playerPtr);

private:

    // 1���ɐ����ł��鐔
    const int MNumGeneratableInOneArea;

    // �G�l�~�[������̓��I�z��
    std::vector<EnemyGenerator*> mEnemyGeneratorList;
    // �G�l�~�[�̓��I�z��
    std::vector<EnemyObject*> mEnemyObjectList;

public:// �Q�b�^�[�Z�b�^�[

    /// <summary>
    /// �G�l�~�[�̓��I�z����擾
    /// </summary>
    /// <returns> �G�l�~�[�̓��I�z�� </returns>
    std::vector<EnemyObject*> GetEnemyObjectList() { return mEnemyObjectList; }
};