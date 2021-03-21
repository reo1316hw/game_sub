#include "PlayerObjectStateSwordIdle.h"
#include "InputSystem.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateSwordIdle::PlayerObjectStateSwordIdle()
    : mIsSprint(false)
    , mIsRun(false)
    , mIsAttack(false)
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
    if (mIsAttack)
    {
        return PlayerState::PLAYER_STATE_ATTACK1;
    }

    if (mIsRun)
    {
        return PlayerState::PLAYER_STATE_SWORD_RUN_LOOP;
    }

    if (swordDelivery)
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
    mIsRun = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) ||
        _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) ||
        _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) ||
        _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D);

    //左Shiftキーが入力されたか
    mIsSprint = _keyState.m_keyboard.GetKeyState(SDL_SCANCODE_LSHIFT);

    //Enterキーが入力されたか
    mIsAttack = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_RETURN);

    //Xキーが入力されたか
    swordDelivery = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_X);
}

void PlayerObjectStateSwordIdle::Enter(PlayerObject* _owner, float _deltaTime)
{
    // アイドル状態のアニメーション再生
    SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
    meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_SWORD_IDLE));
}
