#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
/// <param name="_bossActiveBoxPtr"> 更新させてないオブジェクトを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
/// <param name="_deadObjectPtr"> 更新させてないオブジェクトのポインタ </param>
DeadObjectEnable::DeadObjectEnable(GameObject* _owner, DeadObjectActiveBox* _deadObjectActiveBoxPtr, GameObject* _deadObjectPtr)
	: Component(_owner)
	, mDeadObjectActiveBoxPtr(_deadObjectActiveBoxPtr)
	, mDeadObjectPtr(_deadObjectPtr)
{
}

/// <summary>
/// フレーム毎の処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 < /param>
void DeadObjectEnable::Update(float _deltaTime)
{
	if (!mDeadObjectActiveBoxPtr->GetIsHitPlayer() || mDeadObjectPtr->GetState() == eActive)
	{
		return;
	}

	mDeadObjectPtr->SetState(eActive);
}