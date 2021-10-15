#pragma once

/// <summary>
/// エネミーの攻撃判定オブジェクト
/// </summary>
class EnemyAttackDecisionObject : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> 親クラスのポインタ </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	EnemyAttackDecisionObject(GameObject* _owner, const Tag& _ObjectTag);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyAttackDecisionObject() {};

	/// <summary>
	/// オブジェクトの更新処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

	/// <summary>
	/// 当たり判定を行うようにする
	/// </summary>
	void EnableCollision();

	/// <summary>
	/// 当たり判定を行わないようにする
	/// </summary>
	void DisableCollision();

private:

	/// <summary>
	/// ヒットした時の処理
	/// </summary>
	/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
	void OnCollision(const GameObject& _HitObject)override;

	// 親クラスのポインタ
	GameObject* mOwner;
};