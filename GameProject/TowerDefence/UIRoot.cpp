#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
/// <param name="_bossPtr"> �{�X�̃|�C���^ </param>
/// <param name="_enemyObjectManagerPtr"> �G�l�~�[���Ǘ�����N���X�̃|�C���^ </param>
/// <param name="_enemyActiveBoxPtr"> �G�l�~�[���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_bossActiveBoxPtr"> �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
UIRoot::UIRoot(const Tag& _ObjectTag, PlayerObject* _playerPtr, BossObject* _bossPtr, 
	EnemyObjectManager* _enemyObjectManagerPtr, DeadObjectActiveBox* _enemyActiveBoxPtr,
	DeadObjectActiveBox* _bossActiveBoxPtr)
	: GameObject(_ObjectTag)
	, MPlayerHitPointScale(Vector3(1.0f, 0.5f, 1.0f))
	, MBossHitPointScale(Vector3(1.0f, 0.5f, 1.0f))
	, MDeadEnemyCountScale(Vector3(1.0f, 0.5f, 1.0f))
	, MDeadEnemyCountTextScale(Vector3(1.0f, 0.5f, 1.0f))
	, MDefeatEnemyNumberTextScale(Vector3(1.0f, 0.5f, 1.0f))
	, MOperationExplanationScale(Vector3(0.5f, 0.5f, 1.0f))
	, MPlayerHitPointPosition(Vector3(-800.0f, -400.0f, 0.0f))
	, MBossHitPointPosition(Vector3(400.0f, 400.0f, 0.0f))
	, MDeadEnemyCountPosition(Vector3(-800.0f, 400.0f, 0.0f))
	, MDeadEnemyCountTextPosition(Vector3(-250.0f, 400.0f, 0.0f))
	, MDefeatEnemyNumberTextPosition(Vector3(-220.0f, 400.0f, 0.0f))
	, MOperationExplanationtPosition(Vector3(1100.0f, -400.0f, 0.0f))
{
	// �v���C���[��hp�Q�[�W�𐶐�
	new SpriteGauge(_playerPtr, MPlayerHitPointPosition, "Assets/Texture/PlayerHpGauge.png", Tag::eOther, State::eActive, MPlayerHitPointScale);
	// �v���C���[��hp�̘g�𐶐�
	new SpriteFrame(MPlayerHitPointPosition, "Assets/Texture/PlayerHpFrame.png", Tag::eOther, State::eActive, MPlayerHitPointScale);
	// �{�X��hp�Q�[�W�𐶐�
	SpriteGauge* bossHitPointGaugePtr = new SpriteGauge(_bossPtr, MBossHitPointPosition, "Assets/Texture/EnemyHpGauge.png", Tag::eOther, State::eDead, MBossHitPointScale);
	// �{�X��hp�̘g�𐶐�
	SpriteFrame* bossHitPointFramePtr = new SpriteFrame(MBossHitPointPosition, "Assets/Texture/EnemyHpFrame.png", Tag::eOther, State::eDead, MBossHitPointScale);
	// �|�����G�l�~�[�̃J�E���g�Q�[�W�𐶐�
	SpriteGauge* deadEnemyCountGaugePtr = new SpriteGauge(_enemyObjectManagerPtr, MDeadEnemyCountPosition, "Assets/Texture/EnemyHpGauge.png", Tag::eOther, State::eActive, _enemyObjectManagerPtr, MDeadEnemyCountScale, true);
	// �|�����G�l�~�[�̃J�E���g�t���[���𐶐�
	SpriteFrame* deadEnemyCountFramePtr = new SpriteFrame(MDeadEnemyCountPosition, "Assets/Texture/EnemyHpFrame.png", Tag::eOther, State::eActive, _enemyObjectManagerPtr, MDeadEnemyCountScale);

	// �|�����G�l�~�[�̃J�E���gUI�𐶐�
	DeadEnemyCountText* deadEnemyCountTextPtr = new DeadEnemyCountText(MDeadEnemyCountTextPosition, Tag::eOther, _enemyObjectManagerPtr, MDeadEnemyCountTextScale);
	// �`���[�g���A���G���A�̓|���G�l�~�[�̐���UI�𐶐�
	DefeatEnemyNumberText* defeatTutorialEnemyNumberTextPtr = new DefeatEnemyNumberText(MDefeatEnemyNumberTextPosition, Tag::eOther, State::eActive, 101, _enemyObjectManagerPtr, MDefeatEnemyNumberTextScale);
	// �����ɃG�l�~�[���N���Ă���G���A�̓|���G�l�~�[�̐���UI�𐶐�
	DefeatEnemyNumberText* defeatInfinitelyEnemyNumberTextPtr = new DefeatEnemyNumberText(MDefeatEnemyNumberTextPosition, Tag::eOther, State::eDead, 102, _enemyObjectManagerPtr, MDefeatEnemyNumberTextScale);

	// �������UI�𐶐�
	OperationExplanation* operationExplanationPtr = new OperationExplanation(MOperationExplanationtPosition,"Assets/Texture/EnemyHpFrame.png", Tag::eOther, _playerPtr, MOperationExplanationScale);

	// �{�X��hp�Q�[�W��L���ɂ���R���|�[�l���g�𐶐�
	new DeadObjectEnable(this, _bossActiveBoxPtr, bossHitPointGaugePtr);
	// �{�X��hp�̘g��L���ɂ���R���|�[�l���g�𐶐�
	new DeadObjectEnable(this, _bossActiveBoxPtr, bossHitPointFramePtr);
	// �|�����G�l�~�[�̃J�E���g�Q�[�W��L���ɂ���R���|�[�l���g�𐶐�
	new DeadObjectEnable(this, _enemyActiveBoxPtr, deadEnemyCountGaugePtr);
	// �|�����G�l�~�[�̃J�E���g�t���[����L���ɂ���R���|�[�l���g�𐶐�
	new DeadObjectEnable(this, _enemyActiveBoxPtr, deadEnemyCountFramePtr);
	// �|�����G�l�~�[�̃J�E���gUI��L���ɂ���R���|�[�l���g�𐶐�
	new DeadObjectEnable(this, _enemyActiveBoxPtr, deadEnemyCountTextPtr);
	// �����ɃG�l�~�[���N���Ă���G���A�̓|���G�l�~�[�̐���UI��L���ɂ���R���|�[�l���g�𐶐�
	new DeadObjectEnable(this, _enemyActiveBoxPtr, defeatInfinitelyEnemyNumberTextPtr);
	// �������UI��L���ɂ���R���|�[�l���g�𐶐�
	new DeadObjectEnable(this, _playerPtr, operationExplanationPtr);
}