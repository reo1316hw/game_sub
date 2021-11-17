#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_bossActiveBoxPtr"> ボスを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
/// <param name="_bossBootSemitransparentWallPtr"> ボスが起動することによって出現する半透明の壁のポインタ </param>
BossActiveAffectedObjects::BossActiveAffectedObjects(const Tag& _ObjectTag, BossActiveBox* _bossActiveBoxPtr,
	BossBootSemitransparentWall* _bossBootSemitransparentWallPtr)
	: GameObject(_ObjectTag)
{
	// ボスが起動することによって出現する半透明の壁のON/OFFを行うコンポーネントを生成
	new BossBootSemitransparentWallSwitch(this, _bossActiveBoxPtr, _bossBootSemitransparentWallPtr);
}