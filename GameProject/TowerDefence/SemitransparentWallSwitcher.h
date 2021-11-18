#pragma once

/// <summary>
/// 半透明の壁をON/OFFするオブジェクト
/// </summary>
class SemitransparentWallSwitcher : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	/// <param name="_bossActiveBoxPtr"> 更新していないオブジェクトを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
	/// <param name="_bossBootSemitransparentWallPtr"> 半透明の壁のポインタ </param>
	SemitransparentWallSwitcher(const Tag& _ObjectTag, DeadObjectActiveBox* _deadObjectActiveBoxPtr,
		GameObject* _semitransparentWallPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SemitransparentWallSwitcher() {};

private:
};