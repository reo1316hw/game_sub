#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
/// <param name="_Axis"> 軸 </param>
/// <param name="_AddAngle"> 回転角を増やすための定数 </param>
/// <param name="_OpenToEnemyDefeatNum"> 門を開くために倒すエネミーの数 </param>
/// <param name="_enemysControlerPtr"> エネミーを制御するコンポーネントクラスのポインタ </param>
/// <param name="_selfRotationPtr"> 自身を回転するためのコンポーネントクラスのポインタ </param>
OpenGate::OpenGate(GameObject* _owner, const Vector3& _Axis, const float& _AddAngle, const int& _OpenToDefeatEnemyNum,
	EnemysControler* _enemysControlerPtr, SelfRotation* _selfRotationPtr)
	: Component(_owner)
	, MOpenToDefeatEnemyNum(_OpenToDefeatEnemyNum)
	, MAddAngle(_AddAngle)
	, MOpenAngle(90.0f)
	, MAxis(_Axis)
	, mIsOpen(false)
	, mAngle(0.0f)
	, mEnemysControlerPtr(_enemysControlerPtr)
	, mSelfRotationPtr(_selfRotationPtr)
{
}

/// <summary>
/// フレーム毎の処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void OpenGate::Update(float _deltaTime)
{
	if (Math::Abs(mAngle) > MOpenAngle)
	{
		mIsOpen = false;
		return;
	}

	if (mEnemysControlerPtr->GetDeadCount() >= MOpenToDefeatEnemyNum)
	{
		mIsOpen = true;
	}

	if (mIsOpen)
	{
		mAngle += MAddAngle;

		// 回転処理
		mSelfRotationPtr->Rotation(MAxis, MAddAngle);
	}
}