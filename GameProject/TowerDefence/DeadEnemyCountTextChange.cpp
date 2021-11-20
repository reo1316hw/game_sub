#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
/// <param name="_spriteComponentPtr"> 画像データクラスを管理し、スクリーン上に描画するコンポーネントのポインタ </param>
/// <param name="_enemysControlerPtr"> エネミーを制御するコンポーネントのポインタ </param>
DeadEnemyCountTextChange::DeadEnemyCountTextChange(GameObject* _owner, SpriteComponent* _spriteComponentPtr, EnemysControler* _enemysControlerPtr)
	: Component(_owner)
	, MInitPos(mOwner->GetPosition())
	, MTenPlace(10)
	, MOneHundredPlace(100)
	, MTenPlaceShiftVec(Vector3(-12.0f, 0.0f, 0.0f))
	, MOneHundredPlaceShiftVec(Vector3(-22.0f, 0.0f, 0.0f))
	, mNowDeadEnemyCount(0)
	, mSpriteComponentPtr(_spriteComponentPtr)
	, mEnemysControlerPtr(_enemysControlerPtr)
{
}

/// <summary>
/// フレーム毎の処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 < /param>
void DeadEnemyCountTextChange::Update(float _deltaTime)
{
	// 1フレーム前の倒したエネミーの数
	int preDeadEnemyCount = mNowDeadEnemyCount;

	mNowDeadEnemyCount = mEnemysControlerPtr->GetDeadCount();

	if (preDeadEnemyCount == mNowDeadEnemyCount)
	{
		return;
	}

	if (mNowDeadEnemyCount >= MTenPlace)
	{
		mOwner->SetPosition(MInitPos + MTenPlaceShiftVec);
	}

	if (mNowDeadEnemyCount >= MOneHundredPlace)
	{
		mOwner->SetPosition(MInitPos + MOneHundredPlaceShiftVec);
		return;
	}

	mSpriteComponentPtr->SetTexture(RENDERER->GetFontTexture(mNowDeadEnemyCount));
}