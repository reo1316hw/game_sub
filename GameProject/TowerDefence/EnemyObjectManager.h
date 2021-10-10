#pragma once

// �O���錾
class EnemyGenerator;
class EnemyObject;

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

    void UpdateGameObject(float _deltaTime)override;

private:

    void RemoveEnemyObjectElements();

    // �����^�C�~���O
    const int MCreateTiming;

    // �������s���܂ł̃J�E���g
    int mUntilCreateCount;
    // ����������
    int mCreateCount;

    // �G�l�~�[�̃|�C���^
    EnemyObject* mEnemyObject;

    // �G�l�~�[������v�[��
    std::vector<EnemyGenerator*> mEnemyGeneratorPools;
    // �G�l�~�[�v�[��
    std::vector<EnemyObject*> mEnemyObjectPools;
};