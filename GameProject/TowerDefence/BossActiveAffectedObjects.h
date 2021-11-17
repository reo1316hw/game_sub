#pragma once

/// <summary>
/// ボスがアクティブになることによって影響するオブジェクトの親クラス
/// </summary>
class BossActiveAffectedObjects : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	/// <param name="_bossActiveBoxPtr"> ボスを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
	/// <param name="_bossBootSemitransparentWallPtr"> ボスが起動することによって出現する半透明の壁のポインタ </param>
	BossActiveAffectedObjects(const Tag& _ObjectTag, BossActiveBox* _bossActiveBoxPtr,
		BossBootSemitransparentWall* _bossBootSemitransparentWallPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BossActiveAffectedObjects() {};

private:
};