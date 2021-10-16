#pragma once

// �O���錾
class CreateEnemys;

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
	EnemyObjectManager(const Tag& _ObjectTag);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~EnemyObjectManager() {};

private:

    // �G�l�~�[�����𐶐�����N���X�̃|�C���^
    CreateEnemys* mCreateEnemysPtr;

public:// �Q�b�^�[�Z�b�^�[

    /// <summary>
    /// �G�l�~�[�����𐶐�����N���X�̃|�C���^���擾
    /// </summary>
    /// <returns> �G�l�~�[�����𐶐�����N���X�̃|�C���^ </returns>
    CreateEnemys* GetCreateEnemysPtr() {return mCreateEnemysPtr; }
};