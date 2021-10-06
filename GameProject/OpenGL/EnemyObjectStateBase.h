#pragma once

/// <summary>
/// エネミーステートの基底クラス
/// </summary>
class EnemyObjectStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyObjectStateBase();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~EnemyObjectStateBase() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_owner"> エネミー(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	/// <returns> エネミーの状態 </returns>
	virtual EnemyState Update(EnemyObject* _owner, const float _DeltaTime) = 0;

	/// <summary>
	/// エネミーの状態が変更して、最初に1回だけ呼び出される関数
	/// </summary>
	/// <param name="_owner"> エネミー(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	virtual void Enter(EnemyObject* _owner, const float _DeltaTime) = 0;

	/// <summary>
	/// エネミーの状態が変更して、最後に1回だけ呼び出される関数
	/// </summary>
	/// <param name="_owner"> エネミー(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	virtual void Exit(EnemyObject* _owner, const float _DeltaTime) {};

	/// <summary>
    /// ヒットされた時の処理
    /// </summary>
    /// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
	virtual void OnColision(const GameObject& _HitObject) {};

private:
};