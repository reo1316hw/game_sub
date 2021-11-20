#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチしたオブジェクトのポインタ </param>
/// <param name="_gameObjectPtr"> プレイヤーの基底クラスのポインタ </param>
TextureSizeChanger::TextureSizeChanger(GameObject* _owner, GameObject* _gameObjectPtr)
	: Component(_owner)
	, mNowScaleLeftSideValue(0)
	, mScaleRightSideValue(static_cast<float>(_gameObjectPtr->GetScaleLeftSideValue()))
	, mInitScale(mOwner->GetScale())
	, mGameObjectPtr(_gameObjectPtr)
{
}

/// <summary>
/// フレーム毎の処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void TextureSizeChanger::Update(float _deltaTime)
{
	// 1フレーム前のスケールサイズを求めるための左辺の値
	int mPreScaleLeftSideValue = mNowScaleLeftSideValue;
	// 現在のスケールサイズを求めるための左辺の値
	mNowScaleLeftSideValue = mGameObjectPtr->GetScaleLeftSideValue();

	// 1フレーム前の左辺の値と現在の左辺の値が違ったらテクスチャの横幅を変更
	if (mPreScaleLeftSideValue != mNowScaleLeftSideValue)
	{
		// 収縮率
		float scaleContractionRate = mNowScaleLeftSideValue / mScaleRightSideValue;
		// アタッチしたオブジェクトの大きさ
 		Vector3 scale = Vector3(mInitScale.x * scaleContractionRate, mInitScale.y, mInitScale.z);
		mOwner->SetScale(scale);
	}
}