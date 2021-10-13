#pragma once

// �O���錾
class EnemyGenerator;
class SearchAllEnemy;
class InsertNewEnemy;
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
    ~EnemyObjectManager();
    
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

    // �z��̗v�f������^�C�~���O
    const int MInElementsTiming;

    // �z��̗v�f������܂ł̃J�E���g
    int mUntilInElementsCount;

    // ��ƂȂ�G�l�~�[���G�l�~�[�z�񂩂猟������N���X�̃|�C���^
    SearchAllEnemy* mSearchAllEnemyPtr;
    // �V������������G�l�~�[��z��ɓ����N���X�̃|�C���^
    InsertNewEnemy* mInsertNewEnemyPtr;
    // �G�l�~�[�̃|�C���^
    EnemyObject* mEnemyObjectPtr;

    // �G�l�~�[������̓��I�z��
    std::vector<EnemyGenerator*> mEnemyGeneratorList;
    // �G�l�~�[�̓��I�z��
    std::vector<EnemyObject*> mEnemyObjectList;
};