#pragma once

/// <summary>
/// ボスが起動することによって出現する半透明の壁のON/OFFを行うコンポーネント
/// </summary>
class BossBootSemitransparentWallSwitch : public Component
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
	/// <param name="_bossActiveBoxPtr"> ボスを更新させるための当たり判定用矩形オブジェクトのポインタ </param>
	/// <param name="_bossBootSemitransparentWallPtr"> ボスが起動することによって出現する半透明の壁のポインタ </param>
	BossBootSemitransparentWallSwitch(GameObject* _owner, BossActiveBox* _bossActiveBoxPtr,
		BossBootSemitransparentWall* _bossBootSemitransparentWallPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BossBootSemitransparentWallSwitch() {};

	/// <summary>
	/// フレーム毎の処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 < /param>
	void Update(float _deltaTime)override;

private:

	// ボスを更新させるための当たり判定用矩形オブジェクトのポインタ
	BossActiveBox* mBossActiveBoxPtr;
	// ボスが起動することによって出現する半透明の壁のポインタ
	BossBootSemitransparentWall * mBossBootSemitransparentWallPtr;
};