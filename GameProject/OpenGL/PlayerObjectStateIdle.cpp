#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerObjectStateIdle::PlayerObjectStateIdle()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
/// <returns> プレイヤーの状態 </returns>
PlayerState PlayerObjectStateIdle::Update(PlayerObject* _owner, const float _DeltaTime)
{
    if (mIsSprint)
    {
        if (mIsRun)
        {
            return PlayerState::ePlayerStateSprintStart;
        }
    }
    else if (mIsRun)
    {
        return PlayerState::ePlayerStateRunLoop;
    }

    if (mIsAttack)
    {
        return PlayerState::ePlayerStateFirstAttack;
    }

    return PlayerState::ePlayerStateIdle;
}

/// <summary>
/// 入力処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
void PlayerObjectStateIdle::Input(PlayerObject* _owner, const InputState& _KeyState)
{
   //方向キーが入力されたか
    mIsRun = _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) ||
             _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) ||
             _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) ||
             _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D);

    //左Shiftキーが入力されたか
    mIsSprint = _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_LSHIFT);

    //Spaceキーが入力されたか
    mIsAttack = _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_SPACE);
}

/// <summary>
/// プレイヤーの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void PlayerObjectStateIdle::Enter(PlayerObject* _owner, const float _DeltaTime)
{
    // アイドル状態のアニメーション再生
    SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
    meshcomp->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateIdle));
}
