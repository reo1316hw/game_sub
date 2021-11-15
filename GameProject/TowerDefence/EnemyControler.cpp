#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
/// <param name="_createEnemysPtr"> エネミーたちを生成するクラスのポインタ </param>
EnemyControler::EnemyControler(GameObject* _owner, CreateEnemys* _createEnemysPtr)
	: Component(_owner)
	, MInElementsTiming(300)
	, MMaxActiveInOnce(8)
	, MDistanceThreshold(5000.0f)
	, mUntilInElementsCount(0)
	, mActiveCount(0)
	, mDeadCount(0)
	, mCreateEnemysPtr(_createEnemysPtr)
	, mEnemyHitPointGaugePtr(nullptr)
	, mEnemyHitPointFramePtr(nullptr)
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

	// ボスのポインター
	BossObject* bossObjectPtr = mCreateEnemysPtr->GetBossObjectPtr();

	++mUntilInElementsCount;

	// オブジェクトの数
	int objectCount = 0;

	// 基準となるエネミーを検索
	for (auto referenceEnemyItr : enemyObjectList)
	{
	    ++objectCount;

		// 1フレーム前のhp
		int preHp = mPreHpList[objectCount];
		// 現在のhp
		int nowHp = referenceEnemyItr->GetHitPoint();

		mPreHpList.push_back(nowHp);

		// 1フレーム前のhpと現在のhpが違ったら死んだオブジェクトをカウント
		if (preHp != nowHp && nowHp <= 0)
		{
			++mDeadCount;
		}

		// 一定時間が経ったら非アクティブなエネミーをアクティブにする
		ActiveEnemy(referenceEnemyItr);
	
		if (referenceEnemyItr->GetState() != State::eActive)
		{
			continue;
		}
		
		// 対象となるエネミーを検索
		SearchTargetEnemy(enemyObjectList, referenceEnemyItr);

		if (bossObjectPtr->GetState() != State::eActive)
		{
			continue;
		}

		// 対象となるボスが基準となるエネミーの範囲内に侵入してきたか求める
		InvadeWithinRange(referenceEnemyItr, bossObjectPtr);
		// 対象となるエネミーが基準となるボスの範囲内に侵入してきたか求める
		InvadeWithinRange(bossObjectPtr, referenceEnemyItr);
	}

	// ボスをオブジェクトの数としてカウント
	++objectCount;

	// 1フレーム前のhp
	int preHp = mPreHpList[objectCount];
	// 現在のhp
	int nowHp = bossObjectPtr->GetHitPoint();

	mPreHpList.push_back(nowHp);

	// 1フレーム前のhpと現在のhpが違ったら死んだオブジェクトをカウント
	if (preHp != nowHp && nowHp <= 0)
	{
		++mDeadCount;
	}

	printf("%d\n", mDeadCount);
}

/// <summary>
/// 一定時間が経ったら非アクティブなエネミーをアクティブにする
/// </summary>
/// <param name="_enemyObjectPtr"> エネミーのポインタ </param>
void EnemyControler::ActiveEnemy(EnemyObject* _enemyObjectPtr)
{
	if (mUntilInElementsCount >= MInElementsTiming)
	{
		if (_enemyObjectPtr->GetState() != State::eActive)
		{
			// hpゲージ
			//mEnemyHitPointGaugePtr = _enemyObjectPtr->GetEnemyHitPointGaugePtr();
			// hpの枠
			//mEnemyHitPointFramePtr = _enemyObjectPtr->GetEnemyHitPointFramePtr();

			//mEnemyHitPointGaugePtr->SetState(State::eActive);
			//mEnemyHitPointFramePtr->SetState(State::eActive);
			_enemyObjectPtr->SetState(State::eActive);

			++mActiveCount;
		}

		// 同時にアクティブにできる数を制限
		if (mActiveCount >= MMaxActiveInOnce)
		{
			mActiveCount = 0;
			mUntilInElementsCount = 0;
		}
	}
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

		// 対象となるエネミーが基準となるエネミーの範囲内に侵入してきたか求める
		InvadeWithinRange(_referenceEnemyItr, targetEnemyItr);
	}
}

/// <summary>
/// 範囲内に侵入してきたか求める
/// </summary>
/// <param name="_referenceEnemyItr"> 基準となるオブジェクト </param>
/// <param name="_targetEnemyItr"> 対象となるオブジェクト </param>
void EnemyControler::InvadeWithinRange(GameObject* _referenceEnemyItr, GameObject* _targetEnemyItr)
{
	// 基準となるオブジェクトの座標
	Vector3 referenceEnemyPos = _referenceEnemyItr->GetPosition();
	referenceEnemyPos.z = 0.0f;
	// 対象となるオブジェクトの座標
	Vector3 targetEnemyPos = _targetEnemyItr->GetPosition();
	targetEnemyPos.z = 0.0f;

	// オブジェクト同士の距離
	Vector3 distance = targetEnemyPos - referenceEnemyPos;

	if (distance.LengthSq() <= MDistanceThreshold)
	{
		// オブジェクト同士が重なって、距離が0だったら強制的に距離を作る
		if (distance.LengthSq() <= 0.0f)
		{
			distance = Vector3(1.0f, 1.0f, 0.0f);
		}

		distance.Normalize();
		// オブジェクトの引き離しを行う
		_referenceEnemyItr->Separation(distance);
	}
}