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

// �A�C�h����Ԃ��瑼�̏�Ԃւ̈ڍs
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
    //// �W�����v�L�[�����͂��ꂽ��
   //if (sceneState.Keyboard.GetKeyValue(SDL_SCANCODE_SPACE) == 1)
   //{
   //    return PlayerState::PLAYER_STATE_JUMPSTART;
   //}

   //�����L�[�����͂��ꂽ��
    mIsRun = _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_W) ||
                 _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_S) ||
                 _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_A) ||
                 _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_D);

    //��Shift�L�[�����͂��ꂽ��
    mIsSprint = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_LSHIFT);

    //Enter�L�[�����͂��ꂽ��
    mIsAttack = _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_RETURN);

    //X�L�[�����͂��ꂽ��
    mIsSwordDelivery = _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_X);
}

void PlayerObjectStateIdle::Enter(PlayerObject* _owner, float _deltaTime)
{
    // �A�C�h����Ԃ̃A�j���[�V�����Đ�
    SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
    meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_IDLE));
}
