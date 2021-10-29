#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
CreateEnemys::CreateEnemys(GameObject* _owner)
	: Component(_owner)
	, MNumGeneratableInOneArea(0)
	, mBossObjectPtr(nullptr)
{
}

/// <summary>
/// �G�l�~�[������𐶐�
/// </summary>
/// <param name="_Pos"> ���W </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
void CreateEnemys::CreateEnemyGenerator(const Vector3& _Pos, const Vector3& _Scale, PlayerObject* _playerPtr)
{
	mEnemyGeneratorList.push_back(new EnemyGenerator(_Pos, _Scale, Tag::eEnemyGenerator, _playerPtr));
}

/// <summary>
/// �G�l�~�[�𐶐�
/// </summary>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
/// <param name="_GpskelName"> gpskel�̃p�X </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
void CreateEnemys::CreateEnemyObject(const Vector3& _Scale, const char* _GpmeshName, const char* _GpskelName, const Tag& _ObjectTag, PlayerObject* _playerPtr)
{
	for (int i = 0; i < MNumGeneratableInOneArea; i++)
	{
		for (auto enemyGeneratorItr : mEnemyGeneratorList)
		{
			// ���W
			Vector3 position = enemyGeneratorItr->GetPosition();

			mEnemyObjectList.push_back(new EnemyObject(position, _Scale, "Assets/Model/Enemy/Enemy.gpmesh"
				                       , "Assets/Model/Enemy/Enemy.gpskel", Tag::eEnemy, _playerPtr));
		}
	}
}

/// <summary>
/// �{�X�𐶐�
/// </summary>
/// <param name="_Pos"> ���W </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
/// <param name="_GpskelName"> gpskel�̃p�X </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
/// <returns> �{�X�̃|�C���^ </returns>
BossObject* CreateEnemys::CreateBossObject(const Vector3& _Pos, const Vector3& _Scale, const char* _GpmeshName, const char* _GpskelName, const Tag& _ObjectTag, PlayerObject* _playerPtr)
{
	// �G�l�~�[�{�X�𐶐�
	mBossObjectPtr = new BossObject(_Pos, _Scale, "Assets/Model/Boss/Boss.gpmesh",
		                            "Assets/Model/Boss/Boss.gpskel", Tag::eBoss, _playerPtr);

	return mBossObjectPtr;
}
