#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_spriteComponentPtr"> �摜�f�[�^�N���X���Ǘ����A�X�N���[����ɕ`�悷��R���|�[�l���g�̃|�C���^ </param>
/// <param name="_enemysControlerPtr"> �G�l�~�[�𐧌䂷��R���|�[�l���g�̃|�C���^ </param>
DeadEnemyCountTextChange::DeadEnemyCountTextChange(GameObject* _owner, SpriteComponent* _spriteComponentPtr, EnemysControler* _enemysControlerPtr)
	: Component(_owner)
	, MInitPos(mOwner->GetPosition())
	, MTenPlace(10)
	, MOneHundredPlace(100)
	, MTenPlaceShiftVec(Vector3(-12.0f, 0.0f, 0.0f))
	, MOneHundredPlaceShiftVec(Vector3(-22.0f, 0.0f, 0.0f))
	, mNowDeadEnemyCount(0)
	, mSpriteComponentPtr(_spriteComponentPtr)
	, mEnemysControlerPtr(_enemysControlerPtr)
{
}

/// <summary>
/// �t���[�����̏���
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� < /param>
void DeadEnemyCountTextChange::Update(float _deltaTime)
{
	// 1�t���[���O�̓|�����G�l�~�[�̐�
	int preDeadEnemyCount = mNowDeadEnemyCount;

	mNowDeadEnemyCount = mEnemysControlerPtr->GetDeadCount();

	if (preDeadEnemyCount == mNowDeadEnemyCount)
	{
		return;
	}

	if (mNowDeadEnemyCount >= MTenPlace)
	{
		mOwner->SetPosition(MInitPos + MTenPlaceShiftVec);
	}

	if (mNowDeadEnemyCount >= MOneHundredPlace)
	{
		mOwner->SetPosition(MInitPos + MOneHundredPlaceShiftVec);
		return;
	}

	mSpriteComponentPtr->SetTexture(RENDERER->GetFontTexture(mNowDeadEnemyCount));
}