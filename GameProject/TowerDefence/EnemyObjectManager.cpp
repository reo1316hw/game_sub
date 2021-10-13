#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_ObjectTag"> �^�O </param>
/// <param name="_SceneTag"> �V�[���^�O </param>
EnemyObjectManager::EnemyObjectManager(const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: GameObject(_ObjectTag, _SceneTag)
	, MInOutElementsTiming(300)
	, MMaxNumEnemysExist(100)
	, mUntilInOutElementsCount(0)
	, mEnemyObject(nullptr)
{
	mTag = _ObjectTag;

	// ��ƂȂ�G�l�~�[���G�l�~�[�z�񂩂猟������N���X�𐶐�
	mSearchReferenceEnemyPtr = new SearchReferenceEnemy();
}

EnemyObjectManager::~EnemyObjectManager()
{
	delete mSearchReferenceEnemyPtr;
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
	mEnemyObjectList = mSearchReferenceEnemyPtr->Search(mEnemyObjectList);

	// �V���ȗv�f��z��ɓ���鏈��
	InsertNewElements();
}

/// <summary>
/// �V���ȗv�f��z��ɓ���鏈��
/// </summary>
void EnemyObjectManager::InsertNewElements()
{
	if (mEnemyObjectList.size() < MMaxNumEnemysExist)
	{
		for (auto itr : mEnemyGeneratorList)
		{
			// �G�l�~�[�𐶐�
			mEnemyObject = itr->CreateEnemyObject();
			mEnemyObjectList.push_back(mEnemyObject);
		}
	}
}