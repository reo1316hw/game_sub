#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_ObjectTag"> タグ </param>
/// <param name="_SceneTag"> シーンタグ </param>
EnemyObjectManager::EnemyObjectManager(const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	: GameObject(_ObjectTag, _SceneTag)
	, MInOutElementsTiming(300)
	, MMaxNumEnemysExist(100)
	, mUntilInOutElementsCount(0)
	, mEnemyObject(nullptr)
{
	mTag = _ObjectTag;

	// 基準となるエネミーをエネミー配列から検索するクラスを生成
	mSearchReferenceEnemyPtr = new SearchReferenceEnemy();
}

EnemyObjectManager::~EnemyObjectManager()
{
	delete mSearchReferenceEnemyPtr;
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
	// 基準となるエネミーを検索
	mEnemyObjectList = mSearchReferenceEnemyPtr->Search(mEnemyObjectList);

	// 新たな要素を配列に入れる処理
	InsertNewElements();
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