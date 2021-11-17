#pragma once

/// <summary>
/// エネミーがアクティブになることによって影響するオブジェクトの親クラス
/// </summary>
class EnemyActiveAffectedObjects : public GameObject
{
public:
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	/// <param name="_enemyActiveBoxPtr"> エネミーを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
	/// <param name="_enemyBootSemitransparentWallPtr"> エネミーが起動することによって出現する半透明の壁のポインタ </param>
	EnemyActiveAffectedObjects(const Tag& _ObjectTag, EnemyActiveBox* _enemyActiveBoxPtr,
		EnemyBootSemitransparentWall* _enemyBootSemitransparentWallPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyActiveAffectedObjects() {};

private:
};