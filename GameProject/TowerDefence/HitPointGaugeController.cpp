#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチしたオブジェクトのポインタ </param>
/// <param name="_texture"> テクスチャ情報 </param>
HitPointGaugeController::HitPointGaugeController(GameObject* _owner, Texture* _texture)
	: Component(_owner)
	, mTextureWidthAfterChange(0)
	, mTextureMaxWidth(_texture->GetWidth())
	, mNowHp(0)
	, mMaxHp(static_cast<float>(mOwner->GetHitPoint()))
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
	mNowHp = mOwner->GetHitPoint();

	// 1フレーム前のhpと現在のhpが違ったらテクスチャの横幅を変更
	if (preHp != mNowHp)
	{
		// 縮小率
		float scaleDownRate = mNowHp / mMaxHp;
		mTextureWidthAfterChange = scaleDownRate * mTextureMaxWidth;
	}
}