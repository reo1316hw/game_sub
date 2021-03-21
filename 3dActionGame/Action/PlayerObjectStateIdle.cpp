#include "PlayerObjectStateIdle.h"
#include "InputSystem.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateIdle::PlayerObjectStateIdle()
    : mIsSprint(false)
    , mIsRun(false)
    , mIsAttack(false)
    , mIsSwordDelivery(false)
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
    if (mIsSprint)
    {
        if (mIsRun)
        {
            return PlayerState::PLAYER_STATE_RUN_START;
        }
    }
    else if (mIsRun)
    {
        return PlayerState::PLAYER_STATE_RUN_LOOP;
    }

    if (mIsSwordDelivery)
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
    mIsRun = _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_W) ||
                 _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_S) ||
                 _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_A) ||
                 _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_D);

    //左Shiftキーが入力されたか
    mIsSprint = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_LSHIFT);

    //Enterキーが入力されたか
    mIsAttack = _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_RETURN);

    //Xキーが入力されたか
    mIsSwordDelivery = _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_X);
}

void PlayerObjectStateIdle::Enter(PlayerObject* _owner, float _deltaTime)
{
    // アイドル状態のアニメーション再生
    SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
    meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_IDLE));
}
