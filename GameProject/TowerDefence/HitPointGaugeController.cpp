#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチしたオブジェクトのポインタ </param>
/// <param name="_gameObjectPtr"> プレイヤーの基底クラスのポインタ </param>
HitPointGaugeController::HitPointGaugeController(GameObject* _owner, GameObject* _gameObjectPtr)
	: Component(_owner)
	, mNowHp(0)
	, mMaxHp(static_cast<float>(_gameObjectPtr->GetHitPoint()))
	, mInitScale(mOwner->GetScale())
	, mGameObjectPtr(_gameObjectPtr)
{
}

/// <summary>
/// フレーム毎の処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void HitPointGaugeController::Update(float _deltaTime)
{
	// 1フレーム前のhp
	int preHp = mNowHp;
	// 現在のhp
	mNowHp = mGameObjectPtr->GetHitPoint();

	// 1フレーム前のhpと現在のhpが違ったらテクスチャの横幅を変更
	if (preHp != mNowHp)
	{
		// 縮小率
		float scaleDownRate = mNowHp / mMaxHp;
		// アタッチしたオブジェクトの大きさ
 		Vector3 scale = Vector3(mInitScale.x * scaleDownRate, mInitScale.y, mInitScale.z);
		mOwner->SetScale(scale);
	}
}