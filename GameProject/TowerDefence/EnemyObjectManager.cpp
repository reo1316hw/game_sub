#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_ObjectTag"> タグ </param>
EnemyObjectManager::EnemyObjectManager(const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MInElementsTiming(300)
	, mUntilInElementsCount(0)
	, mEnemyObjectPtr(nullptr)
{
	// 基準となるエネミーをエネミー配列から検索するクラスを生成
	mSearchAllEnemyPtr = new SearchAllEnemy();
	// 新しく生成するエネミーを配列に入れるクラスを生成
	mInsertNewEnemyPtr = new InsertNewEnemy();
}

EnemyObjectManager::~EnemyObjectManager()
{
	delete mSearchAllEnemyPtr;
	delete mInsertNewEnemyPtr;
}

/// <summary>
/// エネミー生成器を生成
/// </summary>
/// <param name="_Pos"> 座標 </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
void EnemyObjectManager::CreateEnemyGenerator(const Vector3& _Pos, const Vector3& _Scale, PlayerObject* _playerPtr)
{
	mEnemyGeneratorList.push_back(new EnemyGenerator(_Pos, _Scale, Tag::eEnemyGenerator, _playerPtr));
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void EnemyObjectManager::UpdateGameObject(float _deltaTime)
{
	// 基準となるエネミーを検索
	mEnemyObjectList = mSearchAllEnemyPtr->Search(mEnemyObjectList);
	
	++mUntilInElementsCount;

	// 生成するタイミングまでカウントしたらエネミーを生成
	if (mUntilInElementsCount >= MInElementsTiming)
	{
		// 新しく生成するエネミーを配列に入れる処理
		mEnemyObjectList = mInsertNewEnemyPtr->Insert(mEnemyObjectList, mEnemyGeneratorList);

		mUntilInElementsCount = 0;
	}
}