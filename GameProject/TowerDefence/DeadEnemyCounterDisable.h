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
	/// <param name="_DefeatEnemyNum">  倒すエネミーの数 </param>
	/// <param name="_enemysControlerPtr"> エネミーたちを制御するクラスのポインタ </param>
	DeadEnemyCounterDisable(GameObject* _owner, const int& _DefeatEnemyNum, EnemysControler* _enemysControlerPtr);

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

	// 倒すエネミーの数
	const int MDefeatEnemyNum;

	// エネミーを制御するクラスのポインタ
	EnemysControler* mEnemysControlerPtr;
};

