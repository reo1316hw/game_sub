#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
/// <param name="_DefeatEnemyNum">  倒すエネミーの数 </param>
/// <param name="_enemysControlerPtr"> エネミーたちを制御するクラスのポインタ </param>
DeadEnemyCounterDisable::DeadEnemyCounterDisable(GameObject* _owner, const int& _DefeatEnemyNum, EnemysControler* _enemysControlerPtr)
	: Component(_owner)
	, MDefeatEnemyNum(_DefeatEnemyNum)
	, mEnemysControlerPtr(_enemysControlerPtr)
{
}

/// <summary>
/// フレーム毎の処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 < /param>
void DeadEnemyCounterDisable::Update(float _deltaTime)
{
	if (mEnemysControlerPtr->GetDeadCount() < MDefeatEnemyNum)
	{
		return;
	}

	mOwner->SetState(eDead);
}