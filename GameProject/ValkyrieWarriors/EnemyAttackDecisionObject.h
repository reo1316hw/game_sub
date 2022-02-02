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

private:

	// 中心座標との差
	const float MCenterOffset;

	// 親クラスのポインタ
	GameObject* mOwner;
};