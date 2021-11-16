#pragma once

// �O���錾
class CreateEnemys;
class EnemysControler;

/// <summary>
/// �G�l�~�[�̊Ǘ�
/// </summary>
class EnemyObjectManager : public GameObject
{
public:

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
    /// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	EnemyObjectManager(const Tag& _ObjectTag, PlayerObject* _playerPtr);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~EnemyObjectManager() {};

private:

    // �G�l�~�[�����𐶐�����N���X�̃|�C���^
    CreateEnemys* mCreateEnemysPtr;
    // �G�l�~�[�����𐧌䂷��N���X�̃|�C���^
    EnemysControler* mEnemysControlerPtr;

public:// �Q�b�^�[�Z�b�^�[

    /// <summary>
    /// �G�l�~�[�����𐶐�����N���X�̃|�C���^���擾
    /// </summary>
    /// <returns> �G�l�~�[�����𐶐�����N���X�̃|�C���^ </returns>
    CreateEnemys* GetCreateEnemysPtr() {return mCreateEnemysPtr; }

    /// <summary>
    /// �G�l�~�[�����𐧌䂷��N���X�̃|�C���^���擾
    /// </summary>
    /// <returns> �G�l�~�[�����𐧌䂷��N���X�̃|�C���^ </returns>
    EnemysControler* GetEnemysControlerPtr() { return mEnemysControlerPtr; }
};