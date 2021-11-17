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
	, mBossActiveBoxPtr(_bossActiveBoxPtr)
	, mBossHitPointGaugePtr(nullptr)
	, mBossHitPointFramePtr(nullptr)
{
	// �v���C���[��hp�Q�[�W�𐶐�
	new PlayerHitPointGauge(MPlayerHitPointPosition, "Assets/Texture/PlayerHpGauge.png", Tag::eOther, _playerPtr);
	// �v���C���[��hp�̘g�𐶐�
	new PlayerHitPointFrame(MPlayerHitPointPosition, "Assets/Texture/PlayerHpFrame.png", Tag::eOther);
	// �{�X��hp�Q�[�W�𐶐�
	mBossHitPointGaugePtr = new BossHitPointGauge(MBossHitPointPosition, "Assets/Texture/EnemyHpGauge.png", Tag::eOther, _bossPtr);
	// �{�X��hp�̘g�𐶐�
	mBossHitPointFramePtr = new BossHitPointFrame(MBossHitPointPosition, "Assets/Texture/EnemyHpFrame.png", Tag::eOther);
}

/// <summary>
/// �Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void UIRoot::UpdateGameObject(float _deltaTime)
{
	if (!mBossActiveBoxPtr->GetIsHitPlayer() || mBossHitPointGaugePtr->GetState() == eActive 
		&& mBossHitPointFramePtr->GetState() == eActive)
	{
		return;
	}

	mBossHitPointGaugePtr->SetState(eActive);
	mBossHitPointFramePtr->SetState(eActive);
}