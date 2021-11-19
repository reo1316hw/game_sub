#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_DefeatEnemyNum">  �|���G�l�~�[�̐� </param>
/// <param name="_enemysControlerPtr"> �G�l�~�[�����𐧌䂷��N���X�̃|�C���^ </param>
DeadEnemyCounterDisable::DeadEnemyCounterDisable(GameObject* _owner, const int& _DefeatEnemyNum, EnemysControler* _enemysControlerPtr)
	: Component(_owner)
	, MDefeatEnemyNum(_DefeatEnemyNum)
	, mEnemysControlerPtr(_enemysControlerPtr)
{
}

/// <summary>
/// �t���[�����̏���
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� < /param>
void DeadEnemyCounterDisable::Update(float _deltaTime)
{
	if (mEnemysControlerPtr->GetDeadCount() < MDefeatEnemyNum)
	{
		return;
	}

	mOwner->SetState(eDead);
}