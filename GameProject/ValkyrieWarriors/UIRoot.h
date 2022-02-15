#pragma once

// �O���錾
class BossHitPointGauge;
class BossHitPointFrame;

/// <summary>
/// UI���܂Ƃ߂邽�߂̐e�N���X
/// </summary>
class UIRoot : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	/// <param name="_bossPtr"> �{�X�̃|�C���^ </param>
    /// <param name="_enemyObjectManagerPtr"> �G�l�~�[���Ǘ�����N���X�̃|�C���^ </param>
    /// <param name="_enemyActiveBoxPtr"> �G�l�~�[���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
    /// <param name="_bossActiveBoxPtr"> �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
	UIRoot(const Tag& _ObjectTag, PlayerObject* _playerPtr, BossObject* _bossPtr,
        EnemyObjectManager* _enemyObjectManagerPtr, DeadObjectActiveBox* _enemyActiveBoxPtr,
        DeadObjectActiveBox* _bossActiveBoxPtr);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
	~UIRoot() {};

private:

    // �v���C���[��hp�Q�[�W�̑傫��
    const Vector3 MPlayerHitPointScale;
    // �{�X��hp�Q�[�W�̑傫��
    const Vector3 MBossHitPointScale;
    // �|�����G�l�~�[�̃J�E���g�Q�[�W�̑傫��
    const Vector3 MDeadEnemyCountScale;
    // �|�����G�l�~�[�̃J�E���g�e�L�X�g�̑傫��
    const Vector3 MDeadEnemyCountTextScale;
    // �|���G�l�~�[�̐��̃e�L�X�g�̑傫��
    const Vector3 MDefeatEnemyNumberTextScale;
    // �������UI�̑傫��
    const Vector3 MOperationExplanationScale;
    // �v���C���[��hp�Q�[�W�̍��W
    const Vector3 MPlayerHitPointPosition;
    // �{�X��hp�Q�[�W�̍��W
    const Vector3 MBossHitPointGaugePosition;
    // �{�X��hp�t���[���̍��W
    const Vector3 MBossHitPointFramePosition;
    // �|�����G�l�~�[�̃J�E���g�Q�[�W�̍��W
    const Vector3 MDeadEnemyCountGaugePosition;
    // �|�����G�l�~�[�̃J�E���g�t���[���̍��W
    const Vector3 MDeadEnemyCountFramePosition;
    // �|�����G�l�~�[�̃J�E���g�e�L�X�g�̍��W
    const Vector3 MDeadEnemyCountTextPosition;
    // �|���G�l�~�[�̐��̃e�L�X�g�̍��W
    const Vector3 MDefeatEnemyNumberTextPosition;
    // �������UI�̍��W
    const Vector3 MOperationExplanationtPosition;
};