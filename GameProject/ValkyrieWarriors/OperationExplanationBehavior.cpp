#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチしたオブジェクトのポインタ </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
OperationExplanationBehavior::OperationExplanationBehavior(GameObject* _owner, PlayerObject* _playerPtr)
	: Component(_owner)
	, MMoveSpeed(20.0f)
	, MStopForDistance(200000.0f)
	, MInitPosition(mOwner->GetPosition())
	, MRightDirVec(Vector3(1.0f, 0.0f, 0.0f))
	, MLeftDirVec(Vector3(-1.0f, 0.0f, 0.0f))
	, mIsDisable(false)
	, mPlayerPtr(_playerPtr)
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

	mIsDisable = false;
	mOwner->SetIsDisable(mIsDisable);

	if (mPlayerPtr->GetNowState() == PlayerState::ePlayerStateIdle &&
		distance.LengthSq() <= MStopForDistance)
	{
		// 速度
		Vector3 velocity = MLeftDirVec * MMoveSpeed;
		position += velocity;
		mOwner->SetPosition(position);

		return;
	}

	if (mPlayerPtr->GetNowState() == PlayerState::ePlayerStateIdle)
	{
		return;
	}

	if (distance.LengthSq() <= 0.0f)
	{
		mIsDisable = true;
		mOwner->SetIsDisable(mIsDisable);
		return;
	}

	// 速度
	Vector3 velocity = MRightDirVec * MMoveSpeed;
	position += velocity;
	mOwner->SetPosition(position);
}