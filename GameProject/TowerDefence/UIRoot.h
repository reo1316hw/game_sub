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
    /// <param name="_bossActiveBoxPtr"> �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
	UIRoot(const Tag& _ObjectTag, PlayerObject* _playerPtr,
        BossObject* _bossPtr, BossActiveBox* _bossActiveBoxPtr);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
	~UIRoot() {};

private:

    // �v���C���[��hp�Q�[�W�̑傫��
    const Vector2 MPlayerHitPointScale;
    // �{�X��hp�Q�[�W�̑傫��
    const Vector2 MBossHitPointScale;
    // �v���C���[��hp�Q�[�W�̍��W
    const Vector3 MPlayerHitPointPosition;
    // �{�X��hp�Q�[�W�̍��W
    const Vector3 MBossHitPointPosition;
};