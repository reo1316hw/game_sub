#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_spriteComponentPtr"> �摜�f�[�^�N���X���Ǘ����A�X�N���[����ɕ`�悷��R���|�[�l���g�̃|�C���^ </param>
/// <param name="_enemysControlerPtr"> �G�l�~�[�𐧌䂷��R���|�[�l���g�̃|�C���^ </param>
DeadEnemyCountTextChange::DeadEnemyCountTextChange(GameObject* _owner, SpriteComponent* _spriteComponentPtr, EnemysControler* _enemysControlerPtr)
	: Component(_owner)
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

	if (mNowDeadEnemyCount >= 10)
	{
		//mOwner->SetPosition(mOwner->GetPosition() + Vector3(-20.0f, 0.0f, 0.0f));
		//mOwner->SetScale(Vector3(2.0f, 1.0f, 1.0f));
	}

	mSpriteComponentPtr->SetTexture(RENDERER->GetFontTexture(mNowDeadEnemyCount));
}