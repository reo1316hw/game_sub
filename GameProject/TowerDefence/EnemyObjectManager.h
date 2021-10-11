#pragma once

// �O���錾
class EnemyGenerator;
class EnemyObject;

/// <summary>
/// �G�l�~�[�̊Ǘ�
/// </summary>
class EnemyObjectManager : public GameObject
{
public:

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="_ObjectTag"> �^�O </param>
    /// <param name="_SceneTag"> �V�[���^�O </param>
	EnemyObjectManager(const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~EnemyObjectManager() {};
    
	/// <summary>
	/// �G�l�~�[������𐶐�
	/// </summary>
    /// <param name="_Pos"> ���W </param>
    /// <param name="_Scale"> �傫�� </param>
    /// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	void CreateEnemyGenerator(const Vector3& _Pos, const Vector3& _Scale, PlayerObject* _playerPtr);

    /// <summary>
    /// �I�u�W�F�N�g�̍X�V����
    /// </summary>
    /// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
    void UpdateGameObject(float _deltaTime)override;

private:

    /// <summary>
    /// ���S��Ԃ̗v�f��z�񂩂�o������
    /// </summary>
    void PutOutDeathElements();

    /// <summary>
    /// �V���ȗv�f��z��ɓ���鏈��
    /// </summary>
    void InsertNewElements();

    /// <summary>
    /// �z��̗v�f���폜
    /// </summary>
    /// <param name="_enemyObjectPtr"> �G�l�~�[�̃|�C���^�[ </param>
    void RemoveEnemyObjectElements(EnemyObject* _enemyObjectPtr);

    // �z��̗v�f���o�����ꂷ��^�C�~���O
    const int MInOutElementsTiming;
    // �G�l�~�[�����݂ł��鐔�̏��
    const int MMaxNumEnemysExist;

    // �z��̗v�f���o�����ꂷ��܂ł̃J�E���g
    int mUntilInOutElementsCount;

    // �G�l�~�[�̃|�C���^
    EnemyObject* mEnemyObject;

    // �G�l�~�[������̓��I�z��
    std::vector<EnemyGenerator*> mEnemyGeneratorList;
    // �G�l�~�[�̓��I�z��
    std::vector<EnemyObject*> mEnemyObjectList;
};