#pragma once

/// <summary>
/// エネミーが起動することによって出現する半透明の壁のON/OFFを行うコンポーネント
/// </summary>
class EnemyBootSemitransparentWallSwitch : public Component
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
	/// <param name="_enemyActiveBoxPtr"> エネミーを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
	/// <param name="_enemyBootSemitransparentWallPtr"> エネミーが起動することによって出現する半透明の壁のポインタ </param>
	EnemyBootSemitransparentWallSwitch(GameObject* _owner, EnemyActiveBox* _enemyActiveBoxPtr,
		EnemyBootSemitransparentWall* _enemyBootSemitransparentWallPt);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyBootSemitransparentWallSwitch() {};

	/// <summary>
	/// フレーム毎の処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 < /param>
	void Update(float _deltaTime)override;

private:

	// エネミーを更新させるための当たり判定用矩形オブジェクトのポインタ
	EnemyActiveBox* mEnemyActiveBoxPtr;
	// エネミーが起動することによって出現する半透明の壁のポインタ
	EnemyBootSemitransparentWall* mEnemyBootSemitransparentWallPtr;
};