#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_ObjectTag"> タグ </param>
/// <param name="_SceneTag"> シーンタグ </param>
EnemyObjectManager::EnemyObjectManager(const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: GameObject(_ObjectTag, _SceneTag)
	, MInOutElementsTiming(300)
	, MMaxNumEnemysExist(1)
	, mUntilInOutElementsCount(0)
	, mEnemyObject(nullptr)
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
	mEnemyGeneratorList.push_back(new EnemyGenerator(_Pos, _Scale, Tag::eEnemyGenerator, SceneBase::tutorial, _playerPtr));
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void EnemyObjectManager::UpdateGameObject(float _deltaTime)
{
	++mUntilInOutElementsCount;

	if (mUntilInOutElementsCount >= MInOutElementsTiming)
	{
		// 死亡状態の要素を配列から出す処理
		PutOutDeathElements();
		// 新たな要素を配列に入れる処理
		InsertNewElements();
		
		mUntilInOutElementsCount = 0;
	}
}

/// <summary>
/// 死亡状態の要素を配列から出す処理
/// </summary>
void EnemyObjectManager::PutOutDeathElements()
{
	for (auto itr : mEnemyObjectList)
	{
		if (itr->GetState() == Dead)
		{
			// 配列の要素を削除
			RemoveEnemyObjectElements(itr);
		}
	}
}

/// <summary>
/// 新たな要素を配列に入れる処理
/// </summary>
void EnemyObjectManager::InsertNewElements()
{
	if (mEnemyObjectList.size() < MMaxNumEnemysExist)
	{
		for (auto itr : mEnemyGeneratorList)
		{
			// エネミーを生成
			mEnemyObject = itr->CreateEnemyObject();
			mEnemyObjectList.push_back(mEnemyObject);
		}
	}
}

/// <summary>
/// 配列の要素を削除
/// </summary>
/// <param name="_enemyObjectPtr"> エネミーのポインター </param>
void EnemyObjectManager::RemoveEnemyObjectElements(EnemyObject* _enemyObjectPt)
{
	auto iter = std::find(mEnemyObjectList.begin(), mEnemyObjectList.end(), _enemyObjectPt);
	if (iter != mEnemyObjectList.end())
	{
		std::iter_swap(iter, mEnemyObjectList.end() - 1);
		mEnemyObjectList.pop_back();
	}
}