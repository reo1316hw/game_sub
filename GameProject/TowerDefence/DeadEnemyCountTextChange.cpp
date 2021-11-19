#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
/// <param name="_spriteComponentPtr"> 画像データクラスを管理し、スクリーン上に描画するコンポーネントのポインタ </param>
/// <param name="_enemysControlerPtr"> エネミーを制御するコンポーネントのポインタ </param>
DeadEnemyCountTextChange::DeadEnemyCountTextChange(GameObject* _owner, SpriteComponent* _spriteComponentPtr, EnemysControler* _enemysControlerPtr)
	: Component(_owner)
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

	if (mNowDeadEnemyCount >= 10)
	{
		//mOwner->SetPosition(mOwner->GetPosition() + Vector3(-20.0f, 0.0f, 0.0f));
		//mOwner->SetScale(Vector3(2.0f, 1.0f, 1.0f));
	}

	mSpriteComponentPtr->SetTexture(RENDERER->GetFontTexture(mNowDeadEnemyCount));
}