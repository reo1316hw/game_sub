#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
/// <param name="_enemyObjectManagerPtr"> 更新しているオブジェクトを更新させないようにするためのオブジェクトの基底クラスのポインタ </param>
ActiveObjectDisable::ActiveObjectDisable(GameObject* _owner, GameObject* _deadForObjectPtr)
	: Component(_owner)
	, mDeadForObjectPtr(_deadForObjectPtr)
{
}

/// <summary>
/// フレーム毎の処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 < /param>
void ActiveObjectDisable::Update(float _deltaTime)
{
	if (!mDeadForObjectPtr->GetIsDisable() || mOwner->GetState() == eDead)
	{
		return;
	}

	mOwner->SetState(eDead);
}