#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_ObjectTag"> �^�O </param>
/// <param name="_SceneTag"> �V�[���^�O </param>
EnemyObjectManager::EnemyObjectManager(const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: GameObject(_ObjectTag, _SceneTag)
	, MInElementsTiming(300)
	, mUntilInElementsCount(0)
	, mEnemyObjectPtr(nullptr)
{
	mTag = _ObjectTag;

	// ��ƂȂ�G�l�~�[���G�l�~�[�z�񂩂猟������N���X�𐶐�
	mSearchAllEnemyPtr = new SearchAllEnemy();
	// �V������������G�l�~�[��z��ɓ����N���X�𐶐�
	mInsertNewEnemyPtr = new InsertNewEnemy();
}

EnemyObjectManager::~EnemyObjectManager()
{
	delete mSearchAllEnemyPtr;
	delete mInsertNewEnemyPtr;
}

/// <summary>
/// �G�l�~�[������𐶐�
/// </summary>
/// <param name="_Pos"> ���W </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
void EnemyObjectManager::CreateEnemyGenerator(const Vector3& _Pos, const Vector3& _Scale, PlayerObject* _playerPtr)
{
	mEnemyGeneratorList.push_back(new EnemyGenerator(_Pos, _Scale, Tag::eEnemyGenerator, SceneBase::tutorial, _playerPtr));
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void EnemyObjectManager::UpdateGameObject(float _deltaTime)
{
	// ��ƂȂ�G�l�~�[������
	mEnemyObjectList = mSearchAllEnemyPtr->Search(mEnemyObjectList);
	
	++mUntilInElementsCount;

	// ��������^�C�~���O�܂ŃJ�E���g������G�l�~�[�𐶐�
	if (mUntilInElementsCount >= MInElementsTiming)
	{
		// �V������������G�l�~�[��z��ɓ���鏈��
		mEnemyObjectList = mInsertNewEnemyPtr->Insert(mEnemyObjectList, mEnemyGeneratorList);

		mUntilInElementsCount = 0;
	}
}