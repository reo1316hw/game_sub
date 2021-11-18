#pragma once

/// <summary>
/// エネミーのhpの枠
/// </summary>
class EnemyHitPointFrame : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_Scale"> 画像の拡大サイズ </param>
	/// <param name="_TextureName"> テクスチャのパス </param>
	/// <param name="_ObjectTag"> ゲームオブジェクトのタグ </param>
	/// <param name="_enemyPtr"> プレイヤーのポインタ </param>
	EnemyHitPointFrame(const Vector3& _Scale, const std::string& _TextureName,
		               const Tag& _ObjectTag, EnemyObject* _enemyPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyHitPointFrame() {};

	/// <summary>
	/// ゲームオブジェクトのアップデート
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	// エネミーからの距離ベクトル
	const Vector3 MOffset;

	// エネミーのポインタ
	EnemyObject* mEnemyPtr;
};