#pragma once

/// <summary>
/// エネミーの生成器
/// </summary>
class EnemyGenerator : GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_Pos"> 座標 </param>
	/// <param name="_Scale"> 大きさ </param>
	/// <param name="_ObjectTag"> タグ </param>
	/// <param name="_SceneTag"> シーンタグ </param>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	EnemyGenerator(const Vector3& _Pos, const Vector3& _Scale, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, PlayerObject* _playerPtr);

	/// <summary>
    /// デストラクタ
    /// </summary>
	~EnemyGenerator() {};

	EnemyObject* CreateEnemyObject();

private:

	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
};