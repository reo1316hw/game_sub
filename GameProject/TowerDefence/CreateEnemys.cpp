#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
CreateEnemys::CreateEnemys(GameObject* _owner)
	: Component(_owner)
	, MNumGeneratableInOneArea(13)
	, MNumGeneratableInTutorialArea(10)
	, mBossObjectPtr(nullptr)
{
}

/// <summary>
/// エネミー生成器を生成
/// </summary>
/// <param name="_Pos"> 座標 </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_Angle"> 回転角 </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
void CreateEnemys::CreateEnemyGenerator(const Vector3& _Pos, const Vector3& _Scale,
	const float& _Angle, PlayerObject* _playerPtr)
{
	mEnemyGeneratorList.push_back(new EnemyGenerator(_Pos, _Scale, _Angle, "Assets/Model/EnemyGenerator/Door.gpmesh", Tag::eEnemyGenerator, _playerPtr));
}

/// <summary>
/// エネミーを生成
/// </summary>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_GpmeshName"> gpmeshのパス </param>
/// <param name="_GpskelName"> gpskelのパス </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
void CreateEnemys::CreateEnemyObject(const Vector3& _Scale, const char* _GpmeshName, const char* _GpskelName,
	const Tag& _ObjectTag, PlayerObject* _playerPtr)
{
	for (int i = 0; i < MNumGeneratableInOneArea; i++)
	{
		for (auto enemyGeneratorItr : mEnemyGeneratorList)
		{
			// 座標
			Vector3 position = enemyGeneratorItr->GetPosition();

			mEnemyObjectList.push_back(new EnemyObject(position, _Scale, "Assets/Model/Enemy/Enemy.gpmesh"
				                       , "Assets/Model/Enemy/Enemy.gpskel", Tag::eEnemy, _playerPtr));
		}
	}
}

/// <summary>
/// エネミーを生成
/// </summary>
/// <param name="_ShouldTutorialUse"> チュートリアルで使用するか </param>
/// <param name="_Pos"> 座標 </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_GpmeshName"> gpmeshのパス </param>
/// <param name="_GpskelName"> gpskelのパス </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
void CreateEnemys::CreateEnemyObject(const bool& _ShouldTutorialUse, const Vector3& _Pos, const Vector3& _Scale, const char* _GpmeshName,
	const char* _GpskelName, const Tag& _ObjectTag, PlayerObject* _playerPtr)
{
	for (int i = 0; i < MNumGeneratableInTutorialArea; i++)
	{
		Vector3 basePosition = _Pos + Vector3(-200.0f, 0.0f, 0.0f);
		Vector3 eachEnemyPosition = Vector3(50.0f, 0.0f, 0.0f) * i;
		Vector3 finalPosition = basePosition + eachEnemyPosition;

		mEnemyObjectList.push_back(new EnemyObject(_ShouldTutorialUse, finalPosition, _Scale, "Assets/Model/Enemy/Enemy.gpmesh"
			, "Assets/Model/Enemy/Enemy.gpskel", Tag::eEnemy, _playerPtr));
	}
}

/// <summary>
/// ボスを生成
/// </summary>
/// <param name="_Pos"> 座標 </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_GpmeshName"> gpmeshのパス </param>
/// <param name="_GpskelName"> gpskelのパス </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
/// <returns> ボスのポインタ </returns>
BossObject* CreateEnemys::CreateBossObject(const Vector3& _Pos, const Vector3& _Scale, const char* _GpmeshName, const char* _GpskelName, const Tag& _ObjectTag, PlayerObject* _playerPtr)
{
	// エネミーボスを生成
	mBossObjectPtr = new BossObject(_Pos, _Scale, "Assets/Model/Boss/Boss.gpmesh",
		                            "Assets/Model/Boss/Boss.gpskel", Tag::eBoss, _playerPtr);

	return mBossObjectPtr;
}
