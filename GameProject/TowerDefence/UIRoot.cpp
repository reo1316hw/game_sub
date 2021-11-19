#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
/// <param name="_bossPtr"> �{�X�̃|�C���^ </param>
/// <param name="_enemyActiveBoxPtr"> �G�l�~�[���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_bossActiveBoxPtr"> �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_enemysControlerPtr"> �G�l�~�[�����𐧌䂷��N���X�̃|�C���^ </param>
UIRoot::UIRoot(const Tag& _ObjectTag, PlayerObject* _playerPtr, BossObject* _bossPtr, DeadObjectActiveBox* _enemyActiveBoxPtr, 
	DeadObjectActiveBox* _bossActiveBoxPtr, EnemysControler* _enemysControlerPtr)
	: GameObject(_ObjectTag)
	, MTutorialDefeatEnemyNum(10)
	, MInfinitelyDefeatEnemyNum(100)
	, MPlayerHitPointScale(Vector3(1.0f, 0.5f, 1.0f))
	, MBossHitPointScale(Vector3(1.0f, 0.5f, 1.0f))
	, MDeadEnemyCountTextScale(Vector3(1.0f, 0.5f, 1.0f))
	, MDefeatEnemyNumberTextScale(Vector3(1.0f, 0.5f, 1.0f))
	, MPlayerHitPointPosition(Vector3(-800.0f, -400.0f, 0.0f))
	, MBossHitPointPosition(Vector3(400.0f, 400.0f, 0.0f))
	, MDeadEnemyCountTextPosition(Vector3(-600.0f, 400.0f, 0.0f))
	, MDefeatEnemyNumberTextPosition(Vector3(-570.0f, 400.0f, 0.0f))
{
	// �v���C���[��hp�Q�[�W�𐶐�
	new PlayerHitPointGauge(MPlayerHitPointPosition, "Assets/Texture/PlayerHpGauge.png", Tag::eOther, _playerPtr, MPlayerHitPointScale);
	// �v���C���[��hp�̘g�𐶐�
	new PlayerHitPointFrame(MPlayerHitPointPosition, "Assets/Texture/PlayerHpFrame.png", Tag::eOther, MPlayerHitPointScale);
	// �{�X��hp�Q�[�W�𐶐�
	BossHitPointGauge* bossHitPointGaugePtr = new BossHitPointGauge(MBossHitPointPosition, "Assets/Texture/EnemyHpGauge.png", Tag::eOther, _bossPtr, MBossHitPointScale);
	// �{�X��hp�̘g�𐶐�
	BossHitPointFrame* bossHitPointFramePtr = new BossHitPointFrame(MBossHitPointPosition, "Assets/Texture/EnemyHpFrame.png", Tag::eOther, MBossHitPointScale);

	// �`���[�g���A���G���A�|�����G�l�~�[�̃J�E���gUI�𐶐�
	DeadEnemyCountText* deadTutorialEnemyCountTextPtr = new DeadEnemyCountText(MDeadEnemyCountTextPosition, Tag::eOther, State::eActive, MTutorialDefeatEnemyNum, _enemysControlerPtr, MDeadEnemyCountTextScale);
	// �|�����G�l�~�[�̃J�E���gUI�𐶐�
	DeadEnemyCountText* deadInfinitelyEnemyCountTextPtr = new DeadEnemyCountText(MDeadEnemyCountTextPosition, Tag::eOther, State::eDead, MInfinitelyDefeatEnemyNum, _enemysControlerPtr, MDeadEnemyCountTextScale);
	// �`���[�g���A���G���A�̓|���G�l�~�[�̐���UI�𐶐�
	DefeatEnemyNumberText* defeatTutorialEnemyNumberTextPtr = new DefeatEnemyNumberText(MDefeatEnemyNumberTextPosition, Tag::eOther, State::eActive, 101, MTutorialDefeatEnemyNum, _enemysControlerPtr, MDefeatEnemyNumberTextScale);
	// �����ɃG�l�~�[���N���Ă���G���A�̓|���G�l�~�[�̐���UI�𐶐�
	DefeatEnemyNumberText* defeatInfinitelyEnemyNumberTextPtr = new DefeatEnemyNumberText(MDefeatEnemyNumberTextPosition, Tag::eOther, State::eDead, 102, MInfinitelyDefeatEnemyNum, _enemysControlerPtr, MDefeatEnemyNumberTextScale);

	// �{�X��hp�Q�[�W��L���ɂ���R���|�[�l���g�𐶐�
	new DeadObjectEnable(this, _bossActiveBoxPtr, bossHitPointGaugePtr);
	// �{�X��hp�̘g��L���ɂ���R���|�[�l���g�𐶐�
	new DeadObjectEnable(this, _bossActiveBoxPtr, bossHitPointFramePtr);
	// �|�����G�l�~�[�̃J�E���gUI��L���ɂ���R���|�[�l���g�𐶐�
	new DeadObjectEnable(this, _enemyActiveBoxPtr, deadInfinitelyEnemyCountTextPtr);
	// �����ɃG�l�~�[���N���Ă���G���A�̓|���G�l�~�[�̐���UI��L���ɂ���R���|�[�l���g�𐶐�
	new DeadObjectEnable(this, _enemyActiveBoxPtr, defeatInfinitelyEnemyNumberTextPtr);
}