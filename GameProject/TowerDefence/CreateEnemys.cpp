#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_enemyObjectManagerPtr"> エネミーマネージャーのポインタ </param>
CreateEnemys::CreateEnemys(EnemyObjectManager* _enemyObjectManagerPtr)
	: Component(_enemyObjectManagerPtr)
	, MNumGeneratableInOneArea(13)
{
}

/// <summary>
/// エネミー生成器を生成
/// </summary>
/// <param name="_Pos"> 座標 </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
void CreateEnemys::CreateEnemyGenerator(const Vector3& _Pos, const Vector3& _Scale, PlayerObject* _playerPtr)
{
	mEnemyGeneratorList.push_back(new EnemyGenerator(_Pos, _Scale, Tag::eEnemyGenerator, _playerPtr));
}

/// <summary>
/// エネミーを生成
/// </summary>
/// <param name="_Pos"> 座標 </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_GpmeshName"> gpmeshのパス </param>
/// <param name="_GpskelName"> gpskelのパス </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
void CreateEnemys::CreateEnemyObject( const char* _GpmeshName, const char* _GpskelName, const Tag& _ObjectTag, PlayerObject* _playerPtr)
{
	for (int i = 0; i < MNumGeneratableInOneArea; i++)
	{
		for (auto enemyGeneratorItr : mEnemyGeneratorList)
		{
			// 座標
			Vector3 position = enemyGeneratorItr->GetPosition();
			// 大きさ
			Vector3 scale = enemyGeneratorItr->GetScale();

			mEnemyObjectList.push_back(new EnemyObject(position, scale, "Assets/Model/Enemy/Enemy.gpmesh"
				                       , "Assets/Model/Enemy/Enemy.gpskel", Tag::eEnemy, _playerPtr));
		}
	}
}