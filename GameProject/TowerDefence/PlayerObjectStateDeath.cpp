#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerObjectStateDeath::PlayerObjectStateDeath()
	: mIsDead(false)
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
		mIsDead = true;
		_owner->SetState(State::eDead);
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
	// 死亡状態のアニメーション再生
	SkeletalMeshComponent* meshComp = _owner->GetSkeletalMeshComponentPtr();
	meshComp->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateDeath));

	mIsDead = false;
}