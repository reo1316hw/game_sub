#pragma once

/// <summary>
/// 半透明の壁を有効にするオブジェクト
/// </summary>
class SemitransparentWallEnabler : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	/// <param name="_bossActiveBoxPtr"> 更新していないオブジェクトを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
	/// <param name="_bossBootSemitransparentWallPtr"> 半透明の壁のポインタ </param>
	SemitransparentWallEnabler(const Tag& _ObjectTag, DeadObjectActiveBox* _deadObjectActiveBoxPtr,
		GameObject* _semitransparentWallPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SemitransparentWallEnabler() {};

private:
};