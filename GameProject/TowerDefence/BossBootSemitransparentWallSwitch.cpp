#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
/// <param name="_bossActiveBoxPtr"> ボスを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
/// <param name="_bossBootSemitransparentWallPtr"> ボスが起動することによって出現する半透明の壁のポインタ </param>
BossBootSemitransparentWallSwitch::BossBootSemitransparentWallSwitch(GameObject* _owner, BossActiveBox* _bossActiveBoxPtr,
	BossBootSemitransparentWall* _bossBootSemitransparentWallPtr)
	: Component(_owner)
	, mBossActiveBoxPtr(_bossActiveBoxPtr)
	, mBossBootSemitransparentWallPtr(_bossBootSemitransparentWallPtr)
{
}

/// <summary>
/// フレーム毎の処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 < /param>
void BossBootSemitransparentWallSwitch::Update(float _deltaTime)
{
	if (!mBossActiveBoxPtr->GetIsHitPlayer() || mBossBootSemitransparentWallPtr->GetState() == eActive)
	{
		return;
	}

	mBossBootSemitransparentWallPtr->SetState(eActive);
}