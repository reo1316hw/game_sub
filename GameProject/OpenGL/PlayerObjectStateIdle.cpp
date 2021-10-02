#include "pch.h"

PlayerObjectStateIdle::PlayerObjectStateIdle()
{
    printf("Create : [PlayerObjectStateBase] PlayerObjectStateIdle\n");
}

PlayerObjectStateIdle::~PlayerObjectStateIdle()
{
    printf("Remove : [PlayerObjectStateBase] PlayerObjectStateIdle\n");
}

// アイドル状態から他の状態への移行
PlayerState PlayerObjectStateIdle::Update(PlayerObject* _owner, float _deltaTime)
{
    if (mSprintFlag)
    {
        if (mRunFlag)
        {
            return PlayerState::ePlayerStateSprintStart;
        }
    }
    else if (mRunFlag)
    {
        return PlayerState::ePlayerStateRunLoop;
    }

    if (mAttackFlag)
    {
        return PlayerState::ePlayerStateFirstAttack;
    }

    return PlayerState::ePlayerStateIdle;
}

void PlayerObjectStateIdle::Input(PlayerObject* _owner, const InputState& _keyState)
{
    //左Shiftキーが入力されたか
    mSprintFlag = _keyState.m_keyboard.GetKeyState(SDL_SCANCODE_LSHIFT) == Held;

   //方向キーが入力されたか
    mRunFlag = _keyState.m_keyboard.GetKeyState(SDL_SCANCODE_W) == Held ||
               _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) == Held ||
               _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) == Held ||
               _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D) == Held;

    //Spaceキーが入力されたか
    mAttackFlag = _keyState.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Released;
}

void PlayerObjectStateIdle::Enter(PlayerObject* _owner, float _deltaTime)
{
    // アイドル状態のアニメーション再生
    SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
    meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::ePlayerStateIdle));
}
