#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerObjectStateDamage::PlayerObjectStateDamage()
	: mHitPoint(0)
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
/// <returns> プレイヤーの状態 </returns>
PlayerState PlayerObjectStateDamage::Update(PlayerObject* _owner, const float _DeltaTime)
{
	if (mHitPoint <= 0)
	{
		return PlayerState::ePlayerStateDeath;
	}

	// アニメーションが終了したらアイドル状態か、次のコンボへ
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		return PlayerState::ePlayerStateIdle;
	}

	return PlayerState::ePlayerStateDamage;
}

/// <summary>
/// プレイヤーの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void PlayerObjectStateDamage::Enter(PlayerObject* _owner, const float _DeltaTime)
{
	// ダメージ状態のアニメーション再生
	SkeletalMeshComponent* meshComp = _owner->GetSkeletalMeshComponentPtr();
	meshComp->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateDamage));

	// ダメージ値
	int damageValue = _owner->GetDamageValue();
	// 体力
	mHitPoint = _owner->GetHitPoint() - damageValue;

	_owner->SetHitPoint(mHitPoint);
}