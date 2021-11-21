#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチしたオブジェクトのポインタ </param>
/// <param name="_gameObjectPtr"> 基底クラスのポインタ </param>
/// <param name="_IsInitScaleChange"> 最初にオブジェクトの大きさの変更を行うか </param>
TextureSizeChanger::TextureSizeChanger(GameObject* _owner, GameObject* _gameObjectPtr, const bool& _IsInitScaleChange)
	: Component(_owner)
	, mNowScaleLeftSideValue(0)
	, mScaleRightSideValue(0)
	, mInitScale(mOwner->GetScale())
	, mGameObjectPtr(_gameObjectPtr)
{
	if (_IsInitScaleChange)
	{
		mNowScaleLeftSideValue = 1;
	}
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
		mScaleRightSideValue = static_cast<float>(mGameObjectPtr->GetScaleRightSideValue());
		// 収縮率
		float scaleContractionRate = mNowScaleLeftSideValue / mScaleRightSideValue;
		// アタッチしたオブジェクトの大きさ
 		Vector3 scale = Vector3(mInitScale.x * scaleContractionRate, mInitScale.y, mInitScale.z);
		mOwner->SetScale(scale);
	}
}