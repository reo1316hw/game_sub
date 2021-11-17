#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_enemyActiveBoxPtr"> エネミーを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
/// <param name="_enemyBootSemitransparentWallPtr"> エネミーが起動することによって出現する半透明の壁のポインタ </param>
EnemyActiveAffectedObjects::EnemyActiveAffectedObjects(const Tag& _ObjectTag, EnemyActiveBox* _enemyActiveBoxPtr,
	EnemyBootSemitransparentWall* _enemyBootSemitransparentWallPtr)
	: GameObject(_ObjectTag)
{
	// エネミーが起動することによって出現する半透明の壁のON/OFFを行うコンポーネントを生成
	new EnemyBootSemitransparentWallSwitch(this, _enemyActiveBoxPtr, _enemyBootSemitransparentWallPtr);
}