#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerObjectStateDeath::PlayerObjectStateDeath(PlayerWeaponObject* _weaponPtr)
	: mWeaponPtr(_weaponPtr)
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
/// <returns> プレイヤーの状態 </returns>
PlayerState PlayerObjectStateDeath::Update(PlayerObject* _owner, const float _DeltaTime)
{
	// アニメーションが終了したら更新を止める
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		mWeaponPtr->SetState(Dead);
		_owner->SetState(Dead);
	}
	return PlayerState::ePlayerStateDeath;
}

/// <summary>
/// プレイヤーの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void PlayerObjectStateDeath::Enter(PlayerObject* _owner, const float _DeltaTime)
{
	// ATTACK1のアニメーション再生
	SkeletalMeshComponent* meshComp = _owner->GetSkeletalMeshComponentPtr();
	meshComp->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateDeath));
}