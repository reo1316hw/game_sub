#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_ObjectTag"> タグ </param>
/// <param name="_SceneTag"> シーンタグ </param>
EnemyObjectManager::EnemyObjectManager(const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: GameObject(_ObjectTag, _SceneTag)
	, MCreateTiming(300)
	, mUntilCreateCount(0)
	, mCreateCount(0)
{
	mTag = _ObjectTag;
}

/// <summary>
/// エネミー生成器を生成
/// </summary>
/// <param name="_Pos"> 座標 </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
void EnemyObjectManager::CreateEnemyGenerator(const Vector3& _Pos, const Vector3& _Scale, PlayerObject* _playerPtr)
{
	mEnemyGeneratorPools.push_back(new EnemyGenerator(_Pos, _Scale, Tag::eEnemyGenerator, SceneBase::tutorial, _playerPtr));
}

void EnemyObjectManager::RemoveEnemyObjectElements()
{
	/*auto iter = std::find(mEnemyObjectPools.begin(), mEnemyObjectPools.end(), mEnemyObject);
	if (iter != mEnemyObjectPools.end())
	{
		std::iter_swap(iter, mEnemyObjectPools.end() - 1);
		mEnemyObjectPools.pop_back();
	}*/

	for (auto itr : mEnemyObjectPools)
	{
		if (itr->GetState() == Dead)
		{
			std::iter_swap(itr, mEnemyObjectPools.end() - 1);
			mEnemyObjectPools.pop_back();
		}
	}
}

void EnemyObjectManager::UpdateGameObject(float _deltaTime)
{
	++mUntilCreateCount;

	if (mUntilCreateCount >= MCreateTiming && mEnemyObjectPools.size() < 100)
	{
		mUntilCreateCount = 0;

		for (auto itr : mEnemyGeneratorPools)
		{
			mEnemyObject = itr->CreateEnemyObject();
			mEnemyObjectPools.push_back(mEnemyObject);
		}
	}

    RemoveEnemyObjectElements();
}