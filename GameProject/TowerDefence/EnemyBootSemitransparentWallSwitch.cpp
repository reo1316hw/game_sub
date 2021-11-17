#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
/// <param name="_enemyActiveBoxPtr"> エネミーを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
/// <param name="_enemyBootSemitransparentWallPtr"> エネミーが起動することによって出現する半透明の壁のポインタ </param>
EnemyBootSemitransparentWallSwitch::EnemyBootSemitransparentWallSwitch(GameObject* _owner, EnemyActiveBox* _enemyActiveBoxPtr, 
	EnemyBootSemitransparentWall* _enemyBootSemitransparentWallPt)
	: Component(_owner)
	, mEnemyActiveBoxPtr(_enemyActiveBoxPtr)
	, mEnemyBootSemitransparentWallPtr(_enemyBootSemitransparentWallPt)
{
}

/// <summary>
/// フレーム毎の処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 < /param>
void EnemyBootSemitransparentWallSwitch::Update(float _deltaTime)
{
	if (!mEnemyActiveBoxPtr->GetIsHitPlayer() || mEnemyBootSemitransparentWallPtr->GetState() == eActive)
	{
		return;
	}

	mEnemyBootSemitransparentWallPtr->SetState(eActive);
}