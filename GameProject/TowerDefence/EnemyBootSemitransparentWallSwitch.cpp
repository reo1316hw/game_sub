#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_enemyActiveBoxPtr"> �G�l�~�[���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_enemyBootSemitransparentWallPtr"> �G�l�~�[���N�����邱�Ƃɂ���ďo�����锼�����̕ǂ̃|�C���^ </param>
EnemyBootSemitransparentWallSwitch::EnemyBootSemitransparentWallSwitch(GameObject* _owner, EnemyActiveBox* _enemyActiveBoxPtr, 
	EnemyBootSemitransparentWall* _enemyBootSemitransparentWallPt)
	: Component(_owner)
	, mEnemyActiveBoxPtr(_enemyActiveBoxPtr)
	, mEnemyBootSemitransparentWallPtr(_enemyBootSemitransparentWallPt)
{
}

/// <summary>
/// �t���[�����̏���
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� < /param>
void EnemyBootSemitransparentWallSwitch::Update(float _deltaTime)
{
	if (!mEnemyActiveBoxPtr->GetIsHitPlayer() || mEnemyBootSemitransparentWallPtr->GetState() == eActive)
	{
		return;
	}

	mEnemyBootSemitransparentWallPtr->SetState(eActive);
}