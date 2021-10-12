#pragma once

class StopLateralMoveEnemy : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> 親クラスのポインタ </param>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	/// <param name="_SceneTag"> シーンのタグ</param>
	StopLateralMoveEnemy(GameObject* _owner, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StopLateralMoveEnemy() {};

	/// <summary>
	/// オブジェクトの更新処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	/// <summary>
	/// ヒットした時の処理
	/// </summary>
	/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
	void OnCollision(const GameObject& _HitObject)override;

	// 親クラスのポインタ
	GameObject* mEnemyOwner;

public:// ゲッターセッター

	GameObject* GetEnemyOwner() { return mEnemyOwner; };
};

