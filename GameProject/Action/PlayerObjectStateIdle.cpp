#include "PlayerObjectStateIdle.h"
#include "InputSystem.h"
#include "SkeletalMeshComponent.h"

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
            return PlayerState::PLAYER_STATE_RUN_START;
        }
    }
    else if (mRunFlag)
    {
        return PlayerState::PLAYER_STATE_RUN_LOOP;
    }

    if (mSwordDeliveryFlag)
    {
        return PlayerState::PLAYER_STATE_DRAWN_SWORD;
    }

    return PlayerState::PLAYER_STATE_IDLE;
}

void PlayerObjectStateIdle::Inipt(PlayerObject* _owner, const InputState& _keyState)
{
    //// ジャンプキーが入力されたか
   //if (sceneState.Keyboard.GetKeyValue(SDL_SCANCODE_SPACE) == 1)
   //{
   //    return PlayerState::PLAYER_STATE_JUMPSTART;
   //}

   //方向キーが入力されたか
    mRunFlag = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) ||
                 _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) ||
                 _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) ||
                 _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D);

    //左Shiftキーが入力されたか
    mSprintFlag = _keyState.m_keyboard.GetKeyState(SDL_SCANCODE_LSHIFT);

    //Xキーが入力されたか
    mSwordDeliveryFlag = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_X);
}

void PlayerObjectStateIdle::Enter(PlayerObject* _owner, float _deltaTime)
{
    // アイドル状態のアニメーション再生
    SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
    meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_IDLE));
}
