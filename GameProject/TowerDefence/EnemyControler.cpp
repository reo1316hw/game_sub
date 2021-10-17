#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_createEnemysPtr"> �G�l�~�[�����𐶐�����N���X�̃|�C���^ </param>
EnemyControler::EnemyControler(GameObject* _owner, CreateEnemys* _createEnemysPtr)
	: Component(_owner)
	, MInElementsTiming(300)
	, MMaxActiveInOnce(8)
	, MDistanceThreshold(5000.0f)
	, mUntilInElementsCount(0)
	, mActiveCount(0)
	, mReferenceEnemyPos(Vector3::Zero)
	, mCreateEnemysPtr(_createEnemysPtr)
{
}

/// <summary>
/// �t���[�����̏���
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void EnemyControler::Update(float _deltaTime)
{
	// �G�l�~�[�̓��I�z��
	std::vector<EnemyObject*> enemyObjectList = mCreateEnemysPtr->GetEnemyObjectList();

	++mUntilInElementsCount;

	// ��ƂȂ�G�l�~�[������
	for (auto referenceEnemyItr : enemyObjectList)
	{
		// ��莞�Ԃ��o�������A�N�e�B�u�ȃG�l�~�[���A�N�e�B�u�ɂ���
		ActiveEnemy(referenceEnemyItr);
	
		if (referenceEnemyItr->GetState() != State::eActive)
		{
			continue;
		}
		
		// ��ƂȂ�G�l�~�[�̍��W
		mReferenceEnemyPos = referenceEnemyItr->GetPosition();
		// �ΏۂƂȂ�G�l�~�[������
		SearchTargetEnemy(enemyObjectList, referenceEnemyItr);
	}
}

/// <summary>
/// ��莞�Ԃ��o�������A�N�e�B�u�ȃG�l�~�[���A�N�e�B�u�ɂ���
/// </summary>
/// <param name="_enemyObjectPtr"> �G�l�~�[�̃|�C���^ </param>
void EnemyControler::ActiveEnemy(EnemyObject* _enemyObjectPtr)
{
	if (mUntilInElementsCount >= MInElementsTiming)
	{
		if (_enemyObjectPtr->GetState() != State::eActive)
		{
			_enemyObjectPtr->SetState(State::eActive);
			++mActiveCount;
		}

		// �����ɃA�N�e�B�u�ɂł��鐔�𐧌�
		if (mActiveCount >= MMaxActiveInOnce)
		{
			mActiveCount = 0;
			mUntilInElementsCount = 0;
		}
	}
}

/// <summary>
/// �ΏۂƂȂ�G�l�~�[������
/// </summary>
/// <param name="_enemyObjectList"> �G�l�~�[�̓��I�z�� </param>
/// <param name="_referenceEnemyItr"> ��ƂȂ�G�l�~�[ </param>
void EnemyControler::SearchTargetEnemy(std::vector<EnemyObject*> _enemyObjectList, EnemyObject* _referenceEnemyItr)
{
	for (auto targetEnemyItr : _enemyObjectList)
	{
		if (targetEnemyItr == _referenceEnemyItr)
		{
			continue;
		}

		if (targetEnemyItr->GetState() != State::eActive)
		{
			continue;
		}

		// �͈͓��ɐN�����Ă��������߂�
		InvadeWithinRange(_referenceEnemyItr, targetEnemyItr);
	}
}

/// <summary>
/// �͈͓��ɐN�����Ă��������߂�
/// </summary>
/// <param name="_referenceEnemyItr"> ��ƂȂ�G�l�~�[ </param>
/// <param name="_targetEnemyItr"> �ΏۂƂȂ�G�l�~�[ </param>
void EnemyControler::InvadeWithinRange(EnemyObject* _referenceEnemyItr, EnemyObject* _targetEnemyItr)
{
	// �ΏۂƂȂ�G�l�~�[�̍��W
	Vector3 targetEnemyPos = _targetEnemyItr->GetPosition();
	// �G�l�~�[���m�̋���
	Vector3 distance = targetEnemyPos - mReferenceEnemyPos;

	if (distance.LengthSq() <= MDistanceThreshold)
	{
		// �G�l�~�[���m���d�Ȃ��āA������0�������狭���I�ɋ��������
		if (distance.LengthSq() <= 0.0f)
		{
			distance = Vector3(1.0f, 1.0f, 0.0f);
		}

		distance.Normalize();
		// �G�l�~�[���m�̋����̈����������s��
		_referenceEnemyItr->Separation(distance);
	}
}