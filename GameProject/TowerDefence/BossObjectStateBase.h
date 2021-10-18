#pragma once

/// <summary>
/// ボスステートの基底クラス
/// </summary>
class BossObjectStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	BossObjectStateBase();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BossObjectStateBase() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_owner"> ボス(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	/// <returns> ボスの状態 </returns>
	virtual BossState Update(BossObject* _owner, const float _DeltaTime) = 0;

	/// <summary>
	/// ボスの状態が変更して、最初に1回だけ呼び出される関数
	/// </summary>
	/// <param name="_owner"> ボス(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	virtual void Enter(BossObject* _owner, const float _DeltaTime) = 0;

	/// <summary>
	/// ボスの状態が変更して、最後に1回だけ呼び出される関数
	/// </summary>
	/// <param name="_owner"> ボス(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	virtual void Exit(BossObject* _owner, const float _DeltaTime) {};

	/// <summary>
	/// ボスとエネミーの引き離し
	/// </summary>
	/// <param name="_owner"> ボス(親)のポインタ </param>
	/// <param name="_SeparationVec"> 対象となるエネミーに向いたベクトル </param>
	virtual void Separation(BossObject* _owner, const Vector3& _DirTargetEnemyVec) {};

	/// <summary>
	/// ヒットした時の処理
	/// </summary>
	/// <param name="_owner"> ボス(親)のポインタ </param>
	/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
	virtual void OnCollision(BossObject* _owner, const GameObject& _HitObject) {};

private:

};