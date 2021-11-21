#pragma once

/// <summary>
/// 倒したエネミーをカウントするオブジェクトを無効にするクラス
/// </summary>
class DeadEnemyCounterDisable : public Component
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
	/// <param name="_enemysControlerPtr"> エネミーたちを制御するクラスのポインタ </param>
	DeadEnemyCounterDisable(GameObject* _owner, EnemysControler* _enemysControlerPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~DeadEnemyCounterDisable() {};

	/// <summary>
	/// フレーム毎の処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 < /param>
	void Update(float _deltaTime)override;

private:

	// 最初に倒すエネミーの数
	const int MFirstDefeatEnemyNum;
	// 次に倒すエネミーの数
	const int MNextDefeatEnemyNum;

	// 倒すエネミーの数
	int mDeadEnemyNum;

	// エネミーを制御するクラスのポインタ
	EnemysControler* mEnemysControlerPtr;
};

