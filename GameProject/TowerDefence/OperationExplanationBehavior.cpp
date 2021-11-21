#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチしたオブジェクトのポインタ </param>
OperationExplanationBehavior::OperationExplanationBehavior(GameObject* _owner)
	: Component(_owner)
	, MInitPosition(mOwner->GetPosition())
{
}

/// <summary>
/// フレーム毎の処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void OperationExplanationBehavior::Update(float _deltaTime)
{
	// 座標
	Vector3 position = mOwner->GetPosition();
	// 距離
	Vector3 distance = position - MInitPosition;

	if (distance.LengthSq() <= 50000.0f)
	{
		// 速度
		Vector3 velocity = Vector3(-1.0f, 0.0f, 0.0f) * 20.0f;
		position += velocity;
		mOwner->SetPosition(position);

		return;
	}
}