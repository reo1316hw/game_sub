#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
/// <param name="_createEnemysPtr"> エネミーたちを生成するクラスのポインタ </param>
/// <param name="_enemyActiveBoxPtr"> エネミーを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
/// <param name="_bossActiveBoxPtr"> ボスを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
EnemysControler::EnemysControler(GameObject* _owner, CreateEnemys* _createEnemysPtr,
	DeadObjectActiveBox* _enemyActiveBoxPtr, DeadObjectActiveBox* _bossActiveBoxPtr)
	: Component(_owner)
	, MInElementsTiming(300)
	, MMaxActiveInOnce(8)
	, MFirstDefeatEnemyNum(10)
	, MNextDefeatEnemyNum(50)
	, MDistanceThreshold(5000.0f)
	, mDefeatEnemyNum(MFirstDefeatEnemyNum)
	, mIsActive(false)
	, mIsDisable(false)
	, mUntilInElementsCount(0)
	, mActiveCount(0)
	, mDeadCount(0)
	, mTutorialEnemyDeadCount(0)
	, mCreateEnemysPtr(_createEnemysPtr)
	, mEnemyActiveBoxPtr(_enemyActiveBoxPtr)
	, mBossActiveBoxPtr(_bossActiveBoxPtr)
	, mEnemyHitPointGaugePtr(nullptr)
	, mEnemyHitPointFramePtr(nullptr)
{
	// オブジェクトのスケールサイズを求めるための右辺の値を設定
	mOwner->SetScaleRightSideValue(mDefeatEnemyNum);
}

/// <summary>
/// フレーム毎の処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void EnemysControler::Update(float _deltaTime)
{
	// エネミーの動的配列
	std::vector<EnemyObject*> enemyObjectList = mCreateEnemysPtr->GetEnemyObjectList();

	// ボスのポインター
	BossObject* bossObjectPtr = mCreateEnemysPtr->GetBossObjectPtr();

	++mUntilInElementsCount;

	// エネミーたちの要素を指定するためのカウント変数
	int enemysCount = 0;
	// エネミーたちの数
	// エネミーの要素数を取得
	int enemysSize = enemyObjectList.size();

	// エネミーを一定数倒したら倒したエネミーの数をリセットして倒すエネミーの数を変更
	if (mDeadCount >= mDefeatEnemyNum)
	{
		mDeadCount = 0;
		mDefeatEnemyNum = MNextDefeatEnemyNum;
		// オブジェクトのスケールサイズを求めるための右辺の値を設定
		mOwner->SetScaleRightSideValue(mDefeatEnemyNum);
		// オブジェクトのスケールサイズを求めるための左辺の値を設定
		mOwner->SetScaleLeftSideValue(mDeadCount);
	}

	mIsDisable = false;

	// 基準となるエネミーを検索
	for (auto referenceEnemyItr : enemyObjectList)
	{
		// エネミーを更新させるための当たり判定用矩形オブジェクトに当たっていたらエネミーを湧かせる
		if (mEnemyActiveBoxPtr->GetIsEnable())
		{
			mIsActive = true;
		}
		
		// エネミーたちを倒した数をカウント
		EnemysDeathCount(enemysCount, enemysSize, referenceEnemyItr);

		++enemysCount;

		if (mIsActive)
		{
			// 一定時間が経ったら非アクティブなエネミーをアクティブにする
			ActiveEnemy(referenceEnemyItr);
		}
	
		if (referenceEnemyItr->GetState() != State::eActive)
		{
			continue;
		}
		
		// 対象となるエネミーを検索
		SearchTargetEnemy(enemyObjectList, referenceEnemyItr);

		// ボスを更新させるための当たり判定用矩形オブジェクトに当たっていたら
		if (mBossActiveBoxPtr->GetIsEnable())
		{
			mIsActive = false;
			// ボスをアクティブにする
			bossObjectPtr->SetState(eActive);
		}

		if (bossObjectPtr->GetState() != State::eActive)
		{
			continue;
		}

		// 対象となるボスが基準となるエネミーの範囲内に侵入してきたか求める
		InvadeWithinRange(referenceEnemyItr, bossObjectPtr);
		// 対象となるエネミーが基準となるボスの範囲内に侵入してきたか求める
		InvadeWithinRange(bossObjectPtr, referenceEnemyItr);
	}

	if (mDeadCount >= mDefeatEnemyNum)
	{
		mIsDisable = true;
	}

	mOwner->SetIsDisable(mIsDisable);
}

/// <summary>
/// 一定時間が経ったら非アクティブなエネミーをアクティブにする
/// </summary>
/// <param name="_enemyObjectPtr"> エネミーのポインタ </param>
void EnemysControler::ActiveEnemy(EnemyObject* _enemyObjectPtr)
{
	if (mUntilInElementsCount >= MInElementsTiming)
	{
		if (_enemyObjectPtr->GetState() != State::eActive && !_enemyObjectPtr->GetShouldTutorialUse())
		{
			// hpゲージ
			mEnemyHitPointGaugePtr = _enemyObjectPtr->GetEnemyHitPointGaugePtr();
			// hpの枠
			mEnemyHitPointFramePtr = _enemyObjectPtr->GetEnemyHitPointFramePtr();

			mEnemyHitPointGaugePtr->SetState(State::eActive);
			mEnemyHitPointFramePtr->SetState(State::eActive);
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
void EnemysControler::SearchTargetEnemy(std::vector<EnemyObject*> _enemyObjectList, EnemyObject* _referenceEnemyItr)
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
void EnemysControler::InvadeWithinRange(GameObject* _referenceEnemyItr, GameObject* _targetEnemyItr)
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

/// <summary>
/// エネミーたちを倒した数をカウント
/// </summary>
/// <param name="_EnemysCount"> エネミーたちの要素を指定するためのカウント変数 </param>
/// <param name="_EnemysSize"> エネミーたちの数 </param>
/// <param name="_gameObject"> ゲームオブジェクトのポインタ </param>
void EnemysControler::EnemysDeathCount(const int& _EnemysCount, const int& _EnemysSize, EnemyObject* _referenceEnemyItr)
{
	if (mTutorialEnemyDeadCount >= 10 && _referenceEnemyItr->GetShouldTutorialUse())
	{
		return;
	}

	// 1フレーム前のhp動的配列の要素がエネミーの数以下だったら要素を追加する
	if (mPreHpList.size() < _EnemysSize)
	{
		mPreHpList.push_back(_referenceEnemyItr->GetMaxHp());
	}

	// 1フレーム前のhp
	int preHp = mPreHpList[_EnemysCount];
	// 現在のhp
	int nowHp = _referenceEnemyItr->GetHitPoint();

	mPreHpList[_EnemysCount] = nowHp;

	// 1フレーム前のhpと現在のhpが違ったら死んだオブジェクトをカウント
	if (preHp != nowHp && nowHp <= 0)
	{
		++mDeadCount;
		// オブジェクトのスケールサイズを求めるための左辺の値を設定
		mOwner->SetScaleLeftSideValue(mDeadCount);

		if (_referenceEnemyItr->GetShouldTutorialUse())
		{
			++mTutorialEnemyDeadCount;
		}
	}
}