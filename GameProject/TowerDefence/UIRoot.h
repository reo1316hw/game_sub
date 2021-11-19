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
    /// <param name="_enemyActiveBoxPtr"> �G�l�~�[���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
    /// <param name="_bossActiveBoxPtr"> �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
    /// <param name="_enemysControlerPtr"> �G�l�~�[�����𐧌䂷��N���X�̃|�C���^ </param>
	UIRoot(const Tag& _ObjectTag, PlayerObject* _playerPtr, BossObject* _bossPtr, DeadObjectActiveBox* _enemyActiveBoxPtr,
        DeadObjectActiveBox* _bossActiveBoxPtr, EnemysControler* _enemysControlerPtr);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
	~UIRoot() {};

private:

    // �`���[�g���A���G���A�œ|���G�l�~�[�̐�
    const int MTutorialDefeatEnemyNum;
    // �����ɃG�l�~�[���N���Ă���G���A�œ|���G�l�~�[�̐�
    const int MInfinitelyDefeatEnemyNum;

    // �v���C���[��hp�Q�[�W�̍��W
    const Vector3 MPlayerHitPointPosition;
    // �{�X��hp�Q�[�W�̍��W
    const Vector3 MBossHitPointPosition;
    // �|�����G�l�~�[�̃J�E���gUI�̍��W
    const Vector3 MDeadEnemyCountTextPosition;
    // �|���G�l�~�[�̐���UI�̍��W
    const Vector3 MDefeatEnemyNumberTextPosition;
    // �v���C���[��hp�Q�[�W�̑傫��
    const Vector3 MPlayerHitPointScale;
    // �{�X��hp�Q�[�W�̑傫��
    const Vector3 MBossHitPointScale;
    // �|�����G�l�~�[�̃J�E���gUI�̑傫��
    const Vector3 MDeadEnemyCountTextScale;
    // �|���G�l�~�[�̐���UI�̑傫��
    const Vector3 MDefeatEnemyNumberTextScale;
};