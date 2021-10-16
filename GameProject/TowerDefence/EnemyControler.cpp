#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_enemyObjectManagerPtr"> エネミーマネージャーのポインタ </param>
/// <param name="_createEnemysPtr"> エネミーたちを生成するクラスのポインタ </param>
EnemyControler::EnemyControler(EnemyObjectManager* _enemyObjectManagerPtr, CreateEnemys* _createEnemysPtr)
	: Component(_enemyObjectManagerPtr)
	, MInElementsTiming(300)
	, MMaxActiveInOnce(8)
	, MDistanceThreshold(5000.0f)
	, mUntilInElementsCount(0)
	, mActiveCount(0)
	, mReferenceEnemyPos(Vector3::Zero)
	, mCreateEnemysPtr(_createEnemysPtr)
{
}

/// <summary>
/// フレーム毎の処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void EnemyControler::Update(float _deltaTime)
{
	// エネミーの動的配列
	std::vector<EnemyObject*> enemyObjectList = mCreateEnemysPtr->GetEnemyObjectList();

	++mUntilInElementsCount;

	// 基準となるエネミーを検索
	for (auto referenceEnemyItr : enemyObjectList)
	{
		// 一定時間が経ったら非アクティブなエネミーをアクティブにする
		if (ActiveEnemy(referenceEnemyItr))
		{
			continue;
		}

		if (referenceEnemyItr->GetState() != State::eActive)
		{
			continue;
		}
		
		// 基準となるエネミーの座標
		mReferenceEnemyPos = referenceEnemyItr->GetPosition();
		// 対象となるエネミーを検索
		SearchTargetEnemy(enemyObjectList, referenceEnemyItr);
	}
}

/// <summary>
/// 一定時間が経ったら非アクティブなエネミーをアクティブにする
/// </summary>
/// <param name="_enemyObjectPtr"> エネミーのポインタ </param>
/// <returns> 検索を続けるか </returns>
bool EnemyControler::ActiveEnemy(EnemyObject* _enemyObjectPtr)
{
	if (mUntilInElementsCount >= MInElementsTiming)
	{
		if (_enemyObjectPtr->GetState() == State::eActive)
		{
			return true;
		}

		_enemyObjectPtr->SetState(State::eActive);

		++mActiveCount;

		if (mActiveCount >= MMaxActiveInOnce)
		{
			mActiveCount = 0;
			mUntilInElementsCount = 0;
		}
	}

	return false;
}

/// <summary>
/// 対象となるエネミーを検索
/// </summary>
/// <param name="_enemyObjectList"> エネミーの動的配列 </param>
/// <param name="_referenceEnemyItr"> 基準となるエネミー </param>
void EnemyControler::SearchTargetEnemy(std::vector<EnemyObject*> _enemyObjectList, EnemyObject* _referenceEnemyItr)
{
	for (auto targetEnemyItr : _enemyObjectList)
	{
		if (targetEnemyItr == _referenceEnemyItr)
		{
			continue;
		}

		if (targetEnemyItr->GetState() != State::eActive)
		{
			continue;
		}

		// 範囲内に侵入してきたか求める
		InvadeWithinRange(_referenceEnemyItr, targetEnemyItr);
	}
}

/// <summary>
/// 範囲内に侵入してきたか求める
/// </summary>
/// <param name="_referenceEnemyItr"> 基準となるエネミー </param>
/// <param name="_targetEnemyItr"> 対象となるエネミー </param>
void EnemyControler::InvadeWithinRange(EnemyObject* _referenceEnemyItr, EnemyObject* _targetEnemyItr)
{
	// 対象となるエネミーの座標
	Vector3 targetEnemyPos = _targetEnemyItr->GetPosition();
	// エネミー同士の距離
	Vector3 distance = targetEnemyPos - mReferenceEnemyPos;

	if (distance.LengthSq() <= MDistanceThreshold && distance.LengthSq() > 0.0f)
	{
		distance.Normalize();
		// エネミー同士の距離の引き離しを行う
		_referenceEnemyItr->Separation(distance);
	}
}