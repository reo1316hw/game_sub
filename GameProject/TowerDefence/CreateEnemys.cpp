#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_enemyObjectManagerPtr"> �G�l�~�[�}�l�[�W���[�̃|�C���^ </param>
CreateEnemys::CreateEnemys(EnemyObjectManager* _enemyObjectManagerPtr)
	: Component(_enemyObjectManagerPtr)
	, MNumGeneratableInOneArea(13)
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
/// <param name="_Pos"> ���W </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
/// <param name="_GpskelName"> gpskel�̃p�X </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
void CreateEnemys::CreateEnemyObject( const char* _GpmeshName, const char* _GpskelName, const Tag& _ObjectTag, PlayerObject* _playerPtr)
{
	for (int i = 0; i < MNumGeneratableInOneArea; i++)
	{
		for (auto enemyGeneratorItr : mEnemyGeneratorList)
		{
			// ���W
			Vector3 position = enemyGeneratorItr->GetPosition();
			// �傫��
			Vector3 scale = enemyGeneratorItr->GetScale();

			mEnemyObjectList.push_back(new EnemyObject(position, scale, "Assets/Model/Enemy/Enemy.gpmesh"
				                       , "Assets/Model/Enemy/Enemy.gpskel", Tag::eEnemy, _playerPtr));
		}
	}
}