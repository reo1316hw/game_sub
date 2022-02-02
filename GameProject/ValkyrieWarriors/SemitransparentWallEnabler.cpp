#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_bossActiveBoxPtr"> ボスを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
/// <param name="_bossBootSemitransparentWallPtr"> 半透明の壁のポインタ </param>
SemitransparentWallEnabler::SemitransparentWallEnabler(const Tag& _ObjectTag, DeadObjectActiveBox* _deadObjectActiveBoxPtr,
	GameObject* _semitransparentWallPtr)
	: GameObject(_ObjectTag)
{
	// ボスが起動することによって出現する半透明の壁を有効にするコンポーネントを生成
	new DeadObjectEnable(this, _deadObjectActiveBoxPtr, _semitransparentWallPtr);
}