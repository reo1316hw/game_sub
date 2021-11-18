#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_bossActiveBoxPtr"> ボスを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
/// <param name="_bossBootSemitransparentWallPtr"> 半透明の壁のポインタ </param>
SemitransparentWallSwitcher::SemitransparentWallSwitcher(const Tag& _ObjectTag, DeadObjectActiveBox* _deadObjectActiveBoxPtr,
	GameObject* _semitransparentWallPtr)
	: GameObject(_ObjectTag)
{
	// ボスが起動することによって出現する半透明の壁のON/OFFを行うコンポーネントを生成
	new DeadObjectSwitch(this, _deadObjectActiveBoxPtr, _semitransparentWallPtr);
}