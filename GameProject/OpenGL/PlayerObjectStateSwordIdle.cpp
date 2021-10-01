#include "pch.h"

PlayerObjectStateSwordIdle::PlayerObjectStateSwordIdle()
{
    printf("Create : [PlayerObjectStateBase] PlayerObjectStateSwordIdle\n");
}

PlayerObjectStateSwordIdle::~PlayerObjectStateSwordIdle()
{
    printf("Remove : [PlayerObjectStateBase] PlayerObjectStateSwordIdle\n");
}

// アイドル状態から他の状態への移行
PlayerState PlayerObjectStateSwordIdle::Update(PlayerObject* _owner, float _deltaTime)
{
    if (mAttackFlag)
    {
        return PlayerState::PLAYER_STATE_ATTACK1;
    }

    if (mRunFlag)
    {
        return PlayerState::PLAYER_STATE_SWORD_RUN_LOOP;
    }

    if (mSwordDeliveryFlag)
    {
        return PlayerState::PLAYER_STATE_SWORD_DELIVERY;
    }

    return PlayerState::PLAYER_STATE_SWORD_IDLE;
}

void PlayerObjectStateSwordIdle::Inipt(PlayerObject* _owner, const InputState& _keyState)
{
    //// ジャンプキーが入力されたか
   //if (sceneState.m_keyboard.GetKeyValue(SDL_SCANCODE_SPACE) == 1)
   //{
   //    return PlayerState::PLAYER_STATE_JUMPSTART;
   //}

   //方向キーが入力されたか
    mRunFlag = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) ||
        _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) ||
        _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) ||
        _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D);

    //Enterキーが入力されたか
    mAttackFlag = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_RETURN);

    //Xキーが入力されたか
    mSwordDeliveryFlag = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_X);
}

void PlayerObjectStateSwordIdle::Enter(PlayerObject* _owner, float _deltaTime)
{
    // アイドル状態のアニメーション再生
    SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
    meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_SWORD_IDLE));
}
