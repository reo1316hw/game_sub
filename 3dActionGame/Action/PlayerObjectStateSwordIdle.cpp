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

// �A�C�h����Ԃ��瑼�̏�Ԃւ̈ڍs
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
    //// �W�����v�L�[�����͂��ꂽ��
   //if (sceneState.m_keyboard.GetKeyValue(SDL_SCANCODE_SPACE) == 1)
   //{
   //    return PlayerState::PLAYER_STATE_JUMPSTART;
   //}

   //�����L�[�����͂��ꂽ��
    mIsRun = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) ||
        _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) ||
        _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) ||
        _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D);

    //��Shift�L�[�����͂��ꂽ��
    mIsSprint = _keyState.m_keyboard.GetKeyState(SDL_SCANCODE_LSHIFT);

    //Enter�L�[�����͂��ꂽ��
    mIsAttack = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_RETURN);

    //X�L�[�����͂��ꂽ��
    swordDelivery = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_X);
}

void PlayerObjectStateSwordIdle::Enter(PlayerObject* _owner, float _deltaTime)
{
    // �A�C�h����Ԃ̃A�j���[�V�����Đ�
    SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
    meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_SWORD_IDLE));
}
