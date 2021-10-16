#pragma once

/// <summary>
/// エネミーの生成器
/// </summary>
class EnemyGenerator : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_Pos"> 座標 </param>
	/// <param name="_Scale"> 大きさ </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	/// <param name="_playerPtr"> プレイヤーのポインタ </param>
	EnemyGenerator(const Vector3& _Pos, const Vector3& _Scale, const Tag& _ObjectTag, PlayerObject* _playerPtr);

	/// <summary>
    /// デストラクタ
    /// </summary>
	~EnemyGenerator() {};

	/// <summary>
	/// エネミーの生成
	/// </summary>
	/// <returns> エネミーのポインタ</returns>
	EnemyObject* CreateEnemyObject();

private:

	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
};