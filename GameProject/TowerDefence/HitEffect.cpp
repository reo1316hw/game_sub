#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>	
/// <param name="_owner"> 親クラスのポインタ </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
HitEffect::HitEffect(GameObject* _owner, const Vector3& _Scale, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MHeightCorrection(Vector3(0.0f, 0.0f, 50.0f))
	, mOwner(_owner)
	, mEffectComponentPtr(nullptr)
{
	// エフェクト生成
	mEffectComponentPtr = new EffectComponent(this, _Scale, u"Assets/Effect/Hit.efk", true, true);
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void HitEffect::UpdateGameObject(float _deltaTime)
{
	// 1フレーム前のhp
	int preHp = mNowHp;
	// 最大hp
	int maxHp = mOwner->GetMaxHp();
	// 現在のhp
	mNowHp = mOwner->GetHitPoint();

	// 1フレーム前のhpと現在のhpが違ったらエフェクトを発生
	if (preHp != mNowHp && maxHp != mNowHp)
	{
		mPosition = mOwner->GetPosition() + MHeightCorrection;
		SetPosition(mPosition);
		SetRotation(mOwner->GetRotation());

		// エフェクトを再生
 		mEffectComponentPtr->PlayEffect();
		
	}
}