#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>	
/// <param name="_owner"> 親クラスのポインタ </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
HitEffect::HitEffect(GameObject* _owner, const Vector3& _Scale, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, mOwner(_owner)
	, mEffectComponentPtr(nullptr)
{
	SetScale(mOwner->GetScale());

	// エフェクト生成
	mEffectComponentPtr = new EffectComponent(this, _Scale, u"Assets/Effect/Hit.efk", true, true);
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void HitEffect::UpdateGameObject(float _deltaTime)
{
	mPosition = mOwner->GetPosition() + Vector3(0.0f, 0.0f, 50.0f);
	SetPosition(mPosition);
	SetRotation(mOwner->GetRotation());

	// 1フレーム前のhp
	int preHp = mNowHp;
	// 最大hp
	int maxHp = mOwner->GetMaxHp();
	// 現在のhp
	mNowHp = mOwner->GetHitPoint();

	// 1フレーム前のhpと現在のhpが違ったらテクスチャの横幅を変更
	if (preHp != mNowHp && maxHp != mNowHp)
	{
		// 再生済みじゃなかったらエフェクトを再生する
		if (mEffectComponentPtr->IsPlayedEffect())
		{
			// エフェクトを再生
			mEffectComponentPtr->PlayEffect();
		}
	}
}