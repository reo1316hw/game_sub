#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_createEnemysPtr"> �G�l�~�[�����𐶐�����N���X�̃|�C���^ </param>
/// <param name="_enemyActiveBoxPtr"> �G�l�~�[���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_bossActiveBoxPtr"> �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
EnemysControler::EnemysControler(GameObject* _owner, CreateEnemys* _createEnemysPtr,
	DeadObjectActiveBox* _enemyActiveBoxPtr, DeadObjectActiveBox* _bossActiveBoxPtr)
	: Component(_owner)
	, MInElementsTiming(300)
	, MMaxActiveInOnce(8)
	, MFirstDefeatEnemyNum(10)
	, MNextDefeatEnemyNum(50)
	, MDistanceThreshold(5000.0f)
	, mDefeatEnemyNum(MFirstDefeatEnemyNum)
	, mIsActive(false)
	, mIsDisable(false)
	, mUntilInElementsCount(0)
	, mActiveCount(0)
	, mDeadCount(0)
	, mTutorialEnemyDeadCount(0)
	, mCreateEnemysPtr(_createEnemysPtr)
	, mEnemyActiveBoxPtr(_enemyActiveBoxPtr)
	, mBossActiveBoxPtr(_bossActiveBoxPtr)
	, mEnemyHitPointGaugePtr(nullptr)
	, mEnemyHitPointFramePtr(nullptr)
{
	// �I�u�W�F�N�g�̃X�P�[���T�C�Y�����߂邽�߂̉E�ӂ̒l��ݒ�
	mOwner->SetScaleRightSideValue(mDefeatEnemyNum);
}

/// <summary>
/// �t���[�����̏���
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void EnemysControler::Update(float _deltaTime)
{
	// �G�l�~�[�̓��I�z��
	std::vector<EnemyObject*> enemyObjectList = mCreateEnemysPtr->GetEnemyObjectList();

	// �{�X�̃|�C���^�[
	BossObject* bossObjectPtr = mCreateEnemysPtr->GetBossObjectPtr();

	++mUntilInElementsCount;

	// �G�l�~�[�����̗v�f���w�肷�邽�߂̃J�E���g�ϐ�
	int enemysCount = 0;
	// �G�l�~�[�����̐�
	// �G�l�~�[�̗v�f�����擾
	int enemysSize = enemyObjectList.size();

	// �G�l�~�[����萔�|������|�����G�l�~�[�̐������Z�b�g���ē|���G�l�~�[�̐���ύX
	if (mDeadCount >= mDefeatEnemyNum)
	{
		mDeadCount = 0;
		mDefeatEnemyNum = MNextDefeatEnemyNum;
		// �I�u�W�F�N�g�̃X�P�[���T�C�Y�����߂邽�߂̉E�ӂ̒l��ݒ�
		mOwner->SetScaleRightSideValue(mDefeatEnemyNum);
		// �I�u�W�F�N�g�̃X�P�[���T�C�Y�����߂邽�߂̍��ӂ̒l��ݒ�
		mOwner->SetScaleLeftSideValue(mDeadCount);
	}

	mIsDisable = false;

	// ��ƂȂ�G�l�~�[������
	for (auto referenceEnemyItr : enemyObjectList)
	{
		// �G�l�~�[���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�ɓ������Ă�����G�l�~�[��N������
		if (mEnemyActiveBoxPtr->GetIsEnable())
		{
			mIsActive = true;
		}
		
		// �G�l�~�[������|���������J�E���g
		EnemysDeathCount(enemysCount, enemysSize, referenceEnemyItr);

		++enemysCount;

		if (mIsActive)
		{
			// ��莞�Ԃ��o�������A�N�e�B�u�ȃG�l�~�[���A�N�e�B�u�ɂ���
			ActiveEnemy(referenceEnemyItr);
		}
	
		if (referenceEnemyItr->GetState() != State::eActive)
		{
			continue;
		}
		
		// �ΏۂƂȂ�G�l�~�[������
		SearchTargetEnemy(enemyObjectList, referenceEnemyItr);

		// �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�ɓ������Ă�����
		if (mBossActiveBoxPtr->GetIsEnable())
		{
			mIsActive = false;
			// �{�X���A�N�e�B�u�ɂ���
			bossObjectPtr->SetState(eActive);
		}

		if (bossObjectPtr->GetState() != State::eActive)
		{
			continue;
		}

		// �ΏۂƂȂ�{�X����ƂȂ�G�l�~�[�͈͓̔��ɐN�����Ă��������߂�
		InvadeWithinRange(referenceEnemyItr, bossObjectPtr);
		// �ΏۂƂȂ�G�l�~�[����ƂȂ�{�X�͈͓̔��ɐN�����Ă��������߂�
		InvadeWithinRange(bossObjectPtr, referenceEnemyItr);
	}

	if (mDeadCount >= mDefeatEnemyNum)
	{
		mIsDisable = true;
	}

	mOwner->SetIsDisable(mIsDisable);
}

/// <summary>
/// ��莞�Ԃ��o�������A�N�e�B�u�ȃG�l�~�[���A�N�e�B�u�ɂ���
/// </summary>
/// <param name="_enemyObjectPtr"> �G�l�~�[�̃|�C���^ </param>
void EnemysControler::ActiveEnemy(EnemyObject* _enemyObjectPtr)
{
	if (mUntilInElementsCount >= MInElementsTiming)
	{
		if (_enemyObjectPtr->GetState() != State::eActive && !_enemyObjectPtr->GetShouldTutorialUse())
		{
			// hp�Q�[�W
			mEnemyHitPointGaugePtr = _enemyObjectPtr->GetEnemyHitPointGaugePtr();
			// hp�̘g
			mEnemyHitPointFramePtr = _enemyObjectPtr->GetEnemyHitPointFramePtr();

			mEnemyHitPointGaugePtr->SetState(State::eActive);
			mEnemyHitPointFramePtr->SetState(State::eActive);
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
void EnemysControler::SearchTargetEnemy(std::vector<EnemyObject*> _enemyObjectList, EnemyObject* _referenceEnemyItr)
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

		// �ΏۂƂȂ�G�l�~�[����ƂȂ�G�l�~�[�͈͓̔��ɐN�����Ă��������߂�
		InvadeWithinRange(_referenceEnemyItr, targetEnemyItr);
	}
}

/// <summary>
/// �͈͓��ɐN�����Ă��������߂�
/// </summary>
/// <param name="_referenceEnemyItr"> ��ƂȂ�I�u�W�F�N�g </param>
/// <param name="_targetEnemyItr"> �ΏۂƂȂ�I�u�W�F�N�g </param>
void EnemysControler::InvadeWithinRange(GameObject* _referenceEnemyItr, GameObject* _targetEnemyItr)
{
	// ��ƂȂ�I�u�W�F�N�g�̍��W
	Vector3 referenceEnemyPos = _referenceEnemyItr->GetPosition();
	referenceEnemyPos.z = 0.0f;
	// �ΏۂƂȂ�I�u�W�F�N�g�̍��W
	Vector3 targetEnemyPos = _targetEnemyItr->GetPosition();
	targetEnemyPos.z = 0.0f;

	// �I�u�W�F�N�g���m�̋���
	Vector3 distance = targetEnemyPos - referenceEnemyPos;

	if (distance.LengthSq() <= MDistanceThreshold)
	{
		// �I�u�W�F�N�g���m���d�Ȃ��āA������0�������狭���I�ɋ��������
		if (distance.LengthSq() <= 0.0f)
		{
			distance = Vector3(1.0f, 1.0f, 0.0f);
		}

		distance.Normalize();
		// �I�u�W�F�N�g�̈����������s��
		_referenceEnemyItr->Separation(distance);
	}
}

/// <summary>
/// �G�l�~�[������|���������J�E���g
/// </summary>
/// <param name="_EnemysCount"> �G�l�~�[�����̗v�f���w�肷�邽�߂̃J�E���g�ϐ� </param>
/// <param name="_EnemysSize"> �G�l�~�[�����̐� </param>
/// <param name="_gameObject"> �Q�[���I�u�W�F�N�g�̃|�C���^ </param>
void EnemysControler::EnemysDeathCount(const int& _EnemysCount, const int& _EnemysSize, EnemyObject* _referenceEnemyItr)
{
	if (mTutorialEnemyDeadCount >= 10 && _referenceEnemyItr->GetShouldTutorialUse())
	{
		return;
	}

	// 1�t���[���O��hp���I�z��̗v�f���G�l�~�[�̐��ȉ���������v�f��ǉ�����
	if (mPreHpList.size() < _EnemysSize)
	{
		mPreHpList.push_back(_referenceEnemyItr->GetMaxHp());
	}

	// 1�t���[���O��hp
	int preHp = mPreHpList[_EnemysCount];
	// ���݂�hp
	int nowHp = _referenceEnemyItr->GetHitPoint();

	mPreHpList[_EnemysCount] = nowHp;

	// 1�t���[���O��hp�ƌ��݂�hp��������玀�񂾃I�u�W�F�N�g���J�E���g
	if (preHp != nowHp && nowHp <= 0)
	{
		++mDeadCount;
		// �I�u�W�F�N�g�̃X�P�[���T�C�Y�����߂邽�߂̍��ӂ̒l��ݒ�
		mOwner->SetScaleLeftSideValue(mDeadCount);

		if (_referenceEnemyItr->GetShouldTutorialUse())
		{
			++mTutorialEnemyDeadCount;
		}
	}
}