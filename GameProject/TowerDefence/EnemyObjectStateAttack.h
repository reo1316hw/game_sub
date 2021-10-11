#pragma once

/// <summary>
/// 攻撃状態
/// </summary>
class EnemyObjectStateAttack : public EnemyObjectStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyObjectStateAttack();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyObjectStateAttack() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_owner"> エネミー(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	/// <returns> エネミーの状態 </returns>
	EnemyState Update(EnemyObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// エネミーの状態が変更して、最初に1回だけ呼び出される関数
	/// </summary>
	/// <param name="_owner"> エネミー(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void Enter(EnemyObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// ヒットした時の処理
	/// </summary>
	/// <param name="_owner"> エネミー(親)のポインタ </param>
	/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
	void OnColision(EnemyObject* _owner, const GameObject& _HitObject)override;

private:

	// 攻撃時の速度
	const float MAttackSpeed;
	// アニメーションの再生速度
	const float MPlayRate;

	// ダメージを受けたか
	bool mIsDamage;
	// エネミーと当たったか
	bool mIsHitEnemy;

	// このステートに入ってからの経過時刻
	float mElapseTime;
	// アニメーション総時間
	float mTotalAnimTime;

	// 座標
	Vector3 mPosition;
};