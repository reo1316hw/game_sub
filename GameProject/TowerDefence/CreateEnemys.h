#pragma once

// �O���錾
class EnemyGenerator;
class EnemyObject;
class BossObject;

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
    /// <param name="_Scale"> �傫�� </param>
    /// <param name="_GpmeshName"> gpmesh�̃p�X </param>
    /// <param name="_GpskelName"> gpskel�̃p�X </param>
    /// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
    /// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
    void CreateEnemyObject(const Vector3& _Scale, const char* _GpmeshName, const char* _GpskelName,
                           const Tag& _ObjectTag, PlayerObject* _playerPtr);

    /// <summary>
    /// �{�X�𐶐�
    /// </summary>
    /// <param name="_Pos"> ���W </param>
    /// <param name="_Scale"> �傫�� </param>
    /// <param name="_GpmeshName"> gpmesh�̃p�X </param>
    /// <param name="_GpskelName"> gpskel�̃p�X </param>
    /// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
    /// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
    void CreateBossObject(const Vector3& _Pos, const Vector3& _Scale, const char* _GpmeshName,
                           const char* _GpskelName, const Tag& _ObjectTag, PlayerObject* _playerPtr);

private:

    // 1���ɐ����ł��鐔
    const int MNumGeneratableInOneArea;

    // �G�l�~�[������̓��I�z��
    std::vector<EnemyGenerator*> mEnemyGeneratorList;
    // �G�l�~�[�̓��I�z��
    std::vector<EnemyObject*> mEnemyObjectList;
    // �{�X�̃|�C���^
    BossObject* mBossObjectPtr;

public:// �Q�b�^�[�Z�b�^�[

    /// <summary>
    /// �G�l�~�[�̓��I�z����擾
    /// </summary>
    /// <returns> �G�l�~�[�̓��I�z�� </returns>
    std::vector<EnemyObject*> GetEnemyObjectList() { return mEnemyObjectList; }

    /// <summary>
    /// �{�X�̃|�C���^���擾
    /// </summary>
    /// <returns> �{�X�̃|�C���^ </returns>
    BossObject* GetBossObjectPtr() { return mBossObjectPtr; }
};