#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
/// <param name="_bossPtr"> �{�X�̃|�C���^ </param>
/// <param name="_bossActiveBoxPtr"> �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
UIRoot::UIRoot(const Tag& _ObjectTag, PlayerObject* _playerPtr,
	BossObject* _bossPtr, BossActiveBox* _bossActiveBoxPtr)
	: GameObject(_ObjectTag)
	, MPlayerHitPointPosition(Vector3(-800.0f, -400.0f, 0.0f))
	, MBossHitPointPosition(Vector3(400.0f, 400.0f, 0.0f))
	, MPlayerHitPointScale(Vector2(1.0f, 0.5f))
	, MBossHitPointScale(Vector2(1.0f, 0.5f))
{
	// �v���C���[��hp�Q�[�W�𐶐�
	new PlayerHitPointGauge(MPlayerHitPointPosition, "Assets/Texture/PlayerHpGauge.png", Tag::eOther, _playerPtr, MPlayerHitPointScale);
	// �v���C���[��hp�̘g�𐶐�
	new PlayerHitPointFrame(MPlayerHitPointPosition, "Assets/Texture/PlayerHpFrame.png", Tag::eOther, MPlayerHitPointScale);
	// �{�X��hp�Q�[�W�𐶐�
	BossHitPointGauge* bossHitPointGaugePtr = new BossHitPointGauge(MBossHitPointPosition, "Assets/Texture/EnemyHpGauge.png", Tag::eOther, _bossPtr, MBossHitPointScale);
	// �{�X��hp�̘g�𐶐�
	BossHitPointFrame* bossHitPointFramePtr = new BossHitPointFrame(MBossHitPointPosition, "Assets/Texture/EnemyHpFrame.png", Tag::eOther, MBossHitPointScale);

	// �{�X�̗̑�UI��ON/OFF���s���R���|�[�l���g�𐶐�
	new BossHitPointUISwitch(this, _bossActiveBoxPtr, bossHitPointGaugePtr, bossHitPointFramePtr);

	// 
	new DeadEnemyCountText(Vector3::Zero, Tag::eOther, Vector2(5.0f, 1.0f));
}